#include "ball.h"

float lagranjInterpolate(const float table[][2],float X); // fix pls
float linearInterpolate(const float table[][2], float X);

ball::ball(TVector v_, TVector u_)
{
    v = v_;
    u = u_;
    w = v + u;
}

float ball::H(float y)
{
    return atm1.get_ro(y) / atm1.get_ro_N0();
}

float ball::get_E()
{
    return c[0] * H(h) * (M_PI * atm1.get_ro_N0()) / 8000.0 * w[0] * linearInterpolate(G7, w[0]);
}

float ball::lagranjInterpolate(const float table[][2],float X)
{
    const int n = 79;
    float L, l;

    X = X / atm1.get_a(h); // Mach number
    L = 0.0;

    for (int i = 0; i < n; i++)
    {
        l = 1.0;

        for (int j = 0; j < n; j++)
            if(i != j)
                l *= (X - table[j][0]) / (table[i][0] - table[j][0]);

        L += table[i][1] * l;
    }
    //std::cout << X << ' ';
    return L;
}

float ball::linearInterpolate(const float table[][2], float X)
{
    const int n = 79;
    float x_0;
    float y_0;
    float x_1;
    float y_1;
    float k;
    float b;

    X = X / atm1.get_a(h); // Mach number

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
