#include "ClothoidList.hh"
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

using G2lib::real_type;
using namespace std;

int main(){
  G2lib::G2solve3arc g2solve3arc;

  double x0 = -1;
  double y0 = 0;
  double th0 = M_PI * 0.9;
  double k0 = 0.2 + 1e-10;

  double x1 = 1;
  double y1 = 0;
  double th1 = -M_PI * 1.001;
  double k1 = 0.2;

  int iter = g2solve3arc.build(x0, y0, th0, k0, x1, y1, th1, k1);
  cout << iter << endl;

  const G2lib::ClothoidCurve &first = g2solve3arc.getS0();
  const G2lib::ClothoidCurve &second = g2solve3arc.getSM();
  const G2lib::ClothoidCurve &third = g2solve3arc.getS1();

  cout << "first\n" << first << endl;
  cout << "second\n" << second << endl;
  cout << "third\n" << third << endl;
  
  // 経路沿いの点を求める
  // 先に代表点を求める弧長パラメータの離散値を求める
  std::vector<double> path1, path2, path3;
  double L1 = first.length();
  double L2 = second.length();
  double L3 = third.length();
  
  double tick = 0.1;
  double npts1 = L1 / tick;
  first.optimized_sample_ISO(0 /*offset*/,
                             npts1 /*npts,default ClothoidCurve.m(line171)*/,
                             M_PI / 45 /*max_angle*/, 
                             path1);

  double npts2 = L2 / tick;
  second.optimized_sample_ISO(0,
                              npts2,
                              M_PI / 45,
                              path2
                              );

  double npts3 = L3 / tick;
  third.optimized_sample_ISO(0,
                             npts3,
                             M_PI / 45,
                             path3);
  
  std::ofstream csv("test.csv");
  for(const auto s : path1){
    csv << first.X(s) << ' ' << first.Y(s) << '\n';
  }
  for(const auto s : path2){
    csv << second.X(s) << ' ' << second.Y(s) << '\n';
  }
  for(const auto s : path3){
    csv << third.X(s) << ' ' << third.Y(s) << '\n';
  }
  
  csv.close();
  // 各セグメントの(弧長, 曲率変化, 両端の曲率)
  cout << first.length() << ',' << first.dkappa() << ',' << first.kappaBegin() << ',' << first.kappaEnd() << endl;
  cout << second.length() << ',' << second.dkappa() << ',' << second.kappaBegin() << ',' << second.kappaEnd() << endl;
  cout << third.length() << ',' << third.dkappa() << ',' << third.kappaBegin() << ',' << third.kappaEnd() << endl;

  G2lib::ClothoidCurve cloth(x0, y0, th0, k0, first.dkappa(), first.length());
  cout << cloth.xEnd() << ',' << cloth.yEnd() << ',' << cloth.thetaEnd() << endl;
}
