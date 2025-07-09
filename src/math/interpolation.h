#ifndef INTERPOLATION_H
#define INTERPOLATION_H

//#include "src/ballistics/atm.h"
//#include <iostream>

// X - bullet veolocity
//float LagranjInterpol(const float table[79][2], float X)
//{
//    const int n = 79; //sizeof(table)/sizeof(table[0]);
//    float L, l;
//
//    X = X / 340.294; // Mach number
//    L = 0.0;
//
//    for (int i = 0; i < n; i++)
//    {
//        l = 1.0;
//
//        for (int j = 0; j < n; j++)
//            if(i != j)
//                l *= (X - table[j][0]) / (table[i][0] - table[j][0]);
//
//        L += table[i][1] * l;
//    }
//    //std::cout << X << ' ';
//    return L;
//}

float LinearInterpol(const float table[][2], float X)
{
    const int n = 79; //sizeof(table)/sizeof(table[0]);
    float x_0;
    float y_0;
    float x_1;
    float y_1;
    float k;
    float b;

    X = X / 340.294; // Mach number

    if (X <= table[0][0])
        return table[0][1];
    else if (X >= table[78][0])
        return table[78][1];

    for (int i = 0; i < n - 1; i++)
        if (X == table[i][0])
            return table[i][1];

    for (int i = 0; i < n - 1; i++)
        if (X >= table[i][0] && X <= table[i + 1][0])
        {
            x_0 = table[i][0];
            y_0 = table[i][1];
            x_1 = table[i + 1][0];
            y_1 = table[i + 1][1];

            k = (y_1 - y_0) / (x_1 - x_0);
            b = y_0 - k * x_0;

            return k * X + b;
        }

    return -1;
}

#endif // INTERPOLATION_H
