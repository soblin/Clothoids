#include <vector>

#include "ClothoidList.hh"
#include <boost/python.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

using d_vector = std::vector<double>;

d_vector extendClothoid(double x0, double y0, double th0, double k0, double dk, double L){
  G2lib::ClothoidCurve clothoid(x0, y0, th0, k0, dk, L);
  d_vector ret;
  ret.emplace_back(clothoid.xEnd());
  ret.emplace_back(clothoid.yEnd());
  ret.emplace_back(clothoid.thetaEnd());
  ret.emplace_back(k0 + dk * L);
  
  return ret;
}

d_vector g2Fitting(double x0, double y0, double th0, double k0, double x1, double y1, double th1, double k1){
  G2lib::G2solve3arc g2solve3arc;

  int iter = g2solve3arc.build(x0, y0, th0, k0, x1, y1, th1, k1);

  const G2lib::ClothoidCurve &first = g2solve3arc.getS0();
  const G2lib::ClothoidCurve &second = g2solve3arc.getSM();
  const G2lib::ClothoidCurve &third = g2solve3arc.getS1();

  d_vector ret;
  // k1, k2, k3
  ret.emplace_back(first.dkappa());
  ret.emplace_back(second.dkappa());
  ret.emplace_back(third.dkappa());
  ret.emplace_back(first.length());
  ret.emplace_back(second.length());
  ret.emplace_back(third.length());

  return ret;
}

d_vector pointsOnClothoid(double x0, double y0, double th0, double k0, double dk, double L, char XY, double tick){
  d_vector arc;
  G2lib::ClothoidCurve clothoid(x0, y0, th0, k0, dk, L);

  int npts = L / tick;
  clothoid.optimized_sample_ISO(0 /*offset*/,
                                npts /*number of points*/,
                                M_PI / 45 /*max angle*/,
                                arc);
  d_vector ret;
  for(const auto s : arc){
    if(XY == 'X') ret.emplace_back(clothoid.X(s));
    else          ret.emplace_back(clothoid.Y(s));
  }
  
  return ret;
}

BOOST_PYTHON_MODULE(PyClothoids){
  using namespace boost::python;
  def("extendClothoid", &extendClothoid);
  def("g2Fitting", &g2Fitting);
  def("pointsOnClothoid", &pointsOnClothoid);

  class_<::d_vector>("d_vector")
      .def(vector_indexing_suite<::d_vector>());
}
