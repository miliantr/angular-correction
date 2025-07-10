#include "ball.h"

ball::ball(TVector v, TVector u)
{
    w = v + u;
}

float ball::H(float y)
{
    return atm1.get_ro(y) / atm1.get_ro_N0();
}

float ball::get_E(float h, float v, int bullet)
{
    return c[bullet] * H(h) * (M_PI * atm1.get_ro_N0()) / 8000.0 * v * linearInterpolate(G7, v);
}

float ball::euler(float x0, float xf, float h)
{
    int c = (xf - x0) / h + 1;
    float x = x0;
    float y = altitude;
    float v = w[0];
    float U = w[0];
    float P = 0;
    float t = 0;
    float nu = 0;
    for (int i = 1; i < c; i++)
    {
        U = U + h * (get_E(y, v, 1));
        P = P + h * (atm1.get_g(y) / pow(U, 2));
        t = t + h * 1 / U;
        nu = nu + h * P;

        a_p = nu / D_y * cos(eps);

        y = altitude + ksi * sin(eps + a_p) - nu;
        v = U * sqrt(1 + pow(P, 2) - 2 * P * sin(eps + a_p));

        x += h;
    }
    return a_p;
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

    X = X / atm1.get_a(altitude); // Mach number

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
