#include "ball.h"

ball::ball()
{

}

float ball::H(float y)
{
    return atm1.get_ro(y) / atm1.get_ro_n0();
}

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


float ball::get_E(float v)
{
    return c[0] * H(h) * (M_PI * atm1.get_ro_n0()) / 8000.0 * v * LinearInterpol(G7, v);
}
