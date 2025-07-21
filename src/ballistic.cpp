//-----------------------------------------------------------------------
//  Source      : ballistic.cpp
//  Created     : 03.07.2025
//  Modified    : 20.07.2025
//  Author      : MD Vladislav
//-----------------------------------------------------------------------

#include "ballistic.h"

//-----------------------------------------------------------------------

#define bullet_velocity float(850.0)
#define bullet_mass float(135.0)
#define bullet_kalibr float(12.7)

//-----------------------------------------------------------------------

Ballistic::Ballistic()
{

}

//-----------------------------------------------------------------------
// Приравнивает 2ые массивы
//-----------------------------------------------------------------------
void equating(float a[][2], const float b[][2]);

//-----------------------------------------------------------------------
// Задает начальные условия
// set_cond(дистанция до цели [м], угол места цели [град],
//          направление ветра (относительно Корд) [град. (-180.0...+180.0)],
//          скорость ветра [м/с], высота начала стрельбы [м], темепратура [к])
//-----------------------------------------------------------------------
void Ballistic::set_cond(float distanse, float eps_,
                         float U_, float U_speed, float altitude, float temperature)
{
    TVector U_vec(2); // Направление ветра
    U_vec[0] = cos(D2R(U_));
    U_vec[1] = sin(D2R(U_));
    TVector V01(2); // Начальная скорость стрельбы
    V01[0] = bullet_velocity;
    V01[1] = 0.0;
    W = V01 + U_vec * U_speed;
    D = distanse;
    eps = eps_;
    alt = altitude;
    T_0 = temperature;
}

//-----------------------------------------------------------------------
// Вычисление баллистических элементов
// calc(тип пули)
// см с[] в const.h
//-----------------------------------------------------------------------
void Ballistic::calc(int type)
{
    bType = type;
    switch(bType)
    {
        default: equating(tab, G7); break;
        case (0):  equating(tab, G7); break;
        case (1):  equating(tab, G7); break;
        case (2):  equating(tab, G1); break;
        case (3):  equating(tab, G7); break;
        case (4):  equating(tab, G7); break;
        case (5):  equating(tab, G1); break;
        case (6):  equating(tab, G7); break;
    }
    integrate(D, 0.001);
    return;
}

//-----------------------------------------------------------------------
// Вычисление функции сопротивления
// calc(высота, скорость)
//-----------------------------------------------------------------------
float Ballistic::calc_E(float y, float veol)
{
    return c[bType] * M_PI * ro_N0 / 8000.0 * calc_H(y)
            * veol * interpolate(tab, veol, calc_yG(y));
}

//-----------------------------------------------------------------------
// Вычисление нормированной плотности воздуха на высоте y
// calc_H(высота)
//-----------------------------------------------------------------------
float Ballistic::calc_H(float y)
{
    return pow(1 + Lambda / T_0 * calc_yG(y), -g_0 / (R_0 * Lambda) - 1);
}

//-----------------------------------------------------------------------
// Вычисление температуры на высоте y в кельвинах
// calc_T(высота)
//-----------------------------------------------------------------------
float Ballistic::calc_T(float y)
{
    return T_0 + Lambda * calc_yG(y);
}

//-----------------------------------------------------------------------
// Вычисление скорости звука на высоте y
// calc_a(высота)
//-----------------------------------------------------------------------
float Ballistic::calc_a(float y)
{
    return Rk * sqrt(calc_T(y));
}

//-----------------------------------------------------------------------
// Вычисление геопотенциальноый высоты
// calc_yG(высота)
//-----------------------------------------------------------------------
float Ballistic::calc_yG(float y)
{
    return y * R_E / (R_E + y);
}

//-----------------------------------------------------------------------
// Вычисление закона изменения g(y)
// calc_g(высота)
//-----------------------------------------------------------------------
float Ballistic::calc_g(float y)
{
    return g_0 * pow(R_E / (R_E * y), 2);
}

//-----------------------------------------------------------------------
// Вычисление числа Маха
// calc_M(скорость, высота)
//-----------------------------------------------------------------------
float Ballistic::calc_M(float veol, float altitude)
{
    return veol / calc_a(altitude);
}

//-----------------------------------------------------------------------
// Интегратор Рунге — Кутты 4го порядка
// integrate(дальность до цели, шаг)
//-----------------------------------------------------------------------
void Ballistic::integrate(float xf, float h)
{
    int c = xf / h + 1;
    float ksi = 0.0;
    float U = W[0];
    float P = 0;
    float t = 0;
    float nu = 0;
    float y = alt;
    float v = U;

    for (int i = 0; i < c; i++)
    {
        auto dUdt = [this, y, v]() { return -calc_E(y, v); };
        auto dPdt = [this](float U_val) { return g_0 / pow(U_val, 2); };
        auto dtdt = [](float U_val) { return 1 / U_val; };
        auto dnudt = [](float P_val) { return P_val; };

        float k1_U = h * dUdt();
        float k1_P = h * dPdt(U);
        float k1_t = h * dtdt(U);
        float k1_nu = h * dnudt(P);

        float k2_U = h * dUdt();
        float k2_P = h * dPdt(U + k1_U / 2);
        float k2_t = h * dtdt(U + k1_U / 2);
        float k2_nu = h * dnudt(P + k1_P / 2);

        float k3_U = h * dUdt();
        float k3_P = h * dPdt(U + k2_U / 2);
        float k3_t = h * dtdt(U + k2_U / 2);
        float k3_nu = h * dnudt(P + k2_P / 2);

        float k4_U = h * dUdt();
        float k4_P = h * dPdt(U + k3_U);
        float k4_t = h * dtdt(U + k3_U);
        float k4_nu = h * dnudt(P + k3_P);

        U += (k1_U + 2 * k2_U + 2 * k3_U + k4_U) / 6;
        P += (k1_P + 2 * k2_P + 2 * k3_P + k4_P) / 6;
        t += (k1_t + 2 * k2_t + 2 * k3_t + k4_t) / 6;
        nu += (k1_nu + 2 * k2_nu + 2 * k3_nu + k4_nu) / 6;

        a_p = asin(nu / D * cos(D2R(eps)));
        //a_p = asin(nu / D * cos(D2R(90 - teta)));
        teta = a_p + eps;

        y = alt + ksi * sin(D2R(teta)) - nu;
        v = U * sqrt(1 + pow(P, 2) - 2 * P * sin(D2R(teta)));

        derivation = clac_der(v, t);

        ksi += h;
    }
    psi = atan2(derivation + t * W[1], D);
    return;
}

//-----------------------------------------------------------------------
// Линейный интерполятор
//-----------------------------------------------------------------------
float Ballistic::interpolate(const float table[][2], float X, float Y)
{
    int n = 74;
    //if (G7 == table)
    //    n = 79;
    float x_0;
    float y_0;
    float x_1;
    float y_1;
    float k;
    float b;

    X = calc_M(X, Y); // Mach number

    if (X <= table[0][0])
        return table[0][1];
    else if (X >= table[n - 1][0])
        return table[n - 1][1];

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

//-----------------------------------------------------------------------
// Рассчет угловой скорости
// integrate(скорость)
//-----------------------------------------------------------------------
float Ballistic::calc_om(float veol)
{
    return 2 * M_PI * veol / reziba;
}

//-----------------------------------------------------------------------
// Рассчет силы Магнуса
// integrate(скорость)
//-----------------------------------------------------------------------
float Ballistic::clac_magnus(float veol)
{
    return 1 / 2 * ro_N0 * pow(veol, 2) * M_PI * pow(bullet_kalibr, 2) / 4 * calc_om(veol);
}

//-----------------------------------------------------------------------
// Боковое отклонение за время полёта t
// clac_der(скорость, время полета)
//-----------------------------------------------------------------------
float Ballistic::clac_der(float veol, float time)
{
    return 1 / 2 * clac_magnus(veol) / bullet_mass * pow(time, 2);
}

void equating(float a[][2], const float b[][2])
{
    int n = 74;
    //if (G7 == b)
    //    n = 79;
    for(int i = 0; i < n; i++)
    {
        a[i][0] = b[i][0];
        a[i][1] = b[i][1];
    }
}
