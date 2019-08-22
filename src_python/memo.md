## 必要なメソッド

OK: (x0, y0, th0, k0)から距離Lだけ, 曲率変化dkを用いて移動した時の行き先のノード及び経路の点のリスト

OK: (x0, y0, th0, k0)から(x1, y1, th1, k1)へとG2fittingしたときの経路の点及び曲率のグラフの頂点(省メモリにするため)

## 手探ってみた

### (x0, y0, th0, k0)から距離Lだけ, 曲率変化dkを用いて移動した時の行き先のノード及び経路の点のリスト

`clothoid = ClothoidCurve(_x0, _y0, _th0, _k, _dk, _L)`を使って, `xEnd(), yEnd(), thetaEnd()`を使えば良い.

### (x0, y0, th0, k0)から(x1, y1, th1, k1)へとG2fittingしたときの経路の点及び曲率のグラフの頂点(省メモリにするため)

G2fittingではClothoidListというクラスを利用する.

ClothoidList()は複数のClothoidCurve()を持っており, ClothoidCurve::plot(), plotAngle(), plotCurvature()を続けて利用することで順番に描写している.

`src_mex/mex_common.h`において`do_length()`という関数が弧長を求めるのに使われている様子. これは`src/Clothoid.hh`における`ClothoidCurve::length()`をcallしている.

plot()においては, 経路を求める点の(おそらく)弧長パラメータを`S = optimized_sample(npts, pi/180, 0)` で勝手に求めてくれて, それに沿って `[X, Y]` を `eval()` してくれている.

## Pythonへの値の返し方

どういうふうに返そうか. ノードの間の接続関係と(x, y, th, k)が与えられていればその間の点の座標はon-the-flyで計算することが可能. よって経路上の点の座標を保持するのはメモリの無駄であるともいえる. その代わり衝突判定のたびに経路上の点の座標を計算しなければいけなくなるが. 時間と空間のトレードオフ.

衝突判定がどのような場合に必要になるかを考えると, 新たにノードを伸ばす場合と, 再接続する場合. 全てのエッジについて座標を維持するよりはましであると思うが.
あとは最終的な経路を作る際に逆向きに求める必要が出てくるが.

[x1, y1, th1, k1] = extendClothoid(x0, y0, th0, k0, dk, L)
リストを2つ返すのは面倒
X = pointsOnClothoid(x0, y0, th0, k0, dk, L, 'X', arclength\_tick)
Y = pointsOnClothoid(x0, y0, th0, k0, dk, L, 'Y', arclength\_tick)
[dk1, dk2, dk3, s1, s2, s3] = g2Fitting(x0, y0, th0, k0, x1, y1, th1, k1)
G2fittingしたノード間は, たとえセグメントが3つあったとしても, それぞれの間で`pointOnClothoid`を使えば良い.
