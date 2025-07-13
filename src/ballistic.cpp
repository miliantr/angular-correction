#include "ballistic.h"

Ballistic::Ballistic()
{

}

void equating(float a[][2], const float b[][2]);

void Ballistic::set_cond(float distanse, float eps_, TVector V,
               TVector U, TVector Cord_angle, float altitude)
{
    W = V + U;
    D = distanse;
    eps = eps_;
    CAng = Cord_angle;
    alt = altitude;
}

void Ballistic::calc(int type)
{
    bType = type;
    switch(bType)
    {
        default: equating(tab, G7); break;
        case 0:  equating(tab, G7); break;
        case 1:  equating(tab, G7); break;
        case 2:  equating(tab, G1); break;
        case 3:  equating(tab, G7); break;
        case 4:  equating(tab, G7); break;
        case 5:  equating(tab, G1); break;
        case 6:  equating(tab, G7); break;
    }
    integrate(ksi, D, 1);
    return;
}

void Ballistic::calc_a_p()
{
    a_p = asin(nu / D * cos(eps));
}

float Ballistic::calc_E(float y, TVector veol)
{
    return c[bType] * calc_H(y) * M_PI * ro_N0 / 8000.0
            * veol[0] * interpolate(tab, veol[0], calc_yG(y));
}

float Ballistic::calc_H(float y)
{
    return pow(1 + Lambda / T_N0 * calc_yG(y), -g_0 / (R_0 * Lambda) - 1);
}

float Ballistic::calc_T(float y)
{
    return T_N0 + Lambda * calc_yG(y);
}

float Ballistic::calc_a(float y)
{
    return Rk * sqrt(calc_T(y));
}

float Ballistic::calc_yG(float y)
{
    return (R_E * y) / (R_E + y);
}

float Ballistic::calc_g(float y)
{
    return g_0 * pow(R_E / (R_E * y), 2);
}

float Ballistic::calc_M(float veol, float altitude)
{
    return veol / calc_a(altitude);
}

void Ballistic::integrate(float x0, float xf, float h)
{
    int c = (xf - x0) / h + 1;
    float x = x0;
    float y = alt;
    float v = W[0];

    U = W[0];
    P = 0;
    t = 0;
    nu = 0;

    for (int i = 1; i < c; i++)
    {
        U = U + h * (calc_E(y, v));
        P = P + h * (calc_g(y) / pow(U, 2));
        t = t + h * 1 / U;
        nu = nu + h * P;

        a_p = nu / D * cos(eps);

        y = alt + ksi * sin(eps + a_p) - nu;
        //v = U * sqrt(1 + pow(P, 2) - 2 * P * sin(eps + a_p));

        x += h;
    }
    return;
}

float Ballistic::interpolate(const float table[][2], float X, float Y)
{
    const int n = 79;
    float x_0;
    float y_0;
    float x_1;
    float y_1;
    float k;
    float b;

    X = calc_M(X, Y); // Mach number

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

void equating(float a[][2], const float b[][2])
{
    for(int i = 0; i < 79; i++)
    {
        a[i][0] = b[i][0];
        a[i][1] = b[i][1];
    }
}
