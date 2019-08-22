# -*- coding: utf-8 -*-
#!/usr/bin/env python

import math
import matplotlib.pyplot as plt
import PyClothoids as cloth

if __name__ == '__main__':
    x0 = -1
    y0 = 0
    th0 = math.pi * 0.9
    k0 = 0.2 + 1e-10

    x1 = 1.0
    y1 = 0.0
    th1 = -math.pi * 1.001
    k1 = 0.2

    [dk1, dk2, dk3, s1, s2, s3] = cloth.g2Fitting(
        x0, y0, th0, k0, x1, y1, th1, k1)

    # 1つ目の点
    [xa, ya, tha, ka] = cloth.extendClothoid(x0, y0, th0, k0, dk1, s1)
    # 2つ目の点
    [xb, yb, thb, kb] = cloth.extendClothoid(xa, ya, tha, ka, dk2, s2)
    # 3つ目の点(x1, y1, th1, k1に一致するはずだが)
    [xc, yc, thc, kc] = cloth.extendClothoid(xb, yb, thb, kb, dk3, s3)
    print xc, yc, thc, kc

    tick = 0.05
    Xa = cloth.pointsOnClothoid(x0, y0, th0, k0, dk1, s1, 'X', tick)
    Ya = cloth.pointsOnClothoid(x0, y0, th0, k0, dk1, s1, 'Y', tick)
    Xb = cloth.pointsOnClothoid(xa, ya, tha, ka, dk2, s2, 'X', tick)
    Yb = cloth.pointsOnClothoid(xa, ya, tha, ka, dk2, s2, 'Y', tick)
    Xc = cloth.pointsOnClothoid(xb, yb, thb, kb, dk3, s3, 'X', tick)
    Yc = cloth.pointsOnClothoid(xb, yb, thb, kb, dk3, s3, 'Y', tick)
    plt.plot(Xa, Ya)
    plt.plot(Xb, Yb)
    plt.plot(Xc, Yc)
    plt.show()
