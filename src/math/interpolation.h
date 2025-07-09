#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "src/ballistics/atm.h"
#include <iostream>
//float interpolate(float x);

// x - bullet veolocity
float interpolate(float x)
{
    atm atm1;
    static const int n = sizeof(G7)/sizeof(G7[0]);
    float L, l;
    float h = 120;

    x = x / atm1.get_a(h); // Mach number
    L = 0.0;

    for (int i = 0; i < n; i++)
    {
        l = 1.0;

        for (int j = 0; j < n; j++)
            if(i != j)
                l *= (x - G7[j][0]) / (G7[i][0] - G7[j][0]);

        L += G7[i][1] * l;
    }
    std::cout << x << ' ';
    return L;
}

#endif // INTERPOLATION_H
