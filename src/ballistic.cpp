#include "ballistic.h"

//#include <iostream>
//#include <fstream>

Ballistic::Ballistic()
{

}

//-----------------------------------------------------------------------
// Приравнивает 2ые массивы
//-----------------------------------------------------------------------
void equating(float a[][2], const float b[][2]);

//-----------------------------------------------------------------------
// Задает начальные условия
// set_cond(дистанция до цели, угол места цели, направление ветра, скорость ветра, высота начала стерьбы)
//-----------------------------------------------------------------------
void Ballistic::set_cond(float distanse, float eps_,
                         float U_, float U_speed, float altitude)
{
    TVector U_vec(2);
    U_vec[0] = cos(D2R(U_));
    U_vec[1] = sin(D2R(U_));
    TVector V01(2); // Начальная скорость стрельбы
    V01[0] = 850.0;
    V01[1] = 0.0;
    W = V01 + U_vec * U_speed;
    D = distanse;
    eps = eps_;
    alt = altitude;
}

//-----------------------------------------------------------------------
// Вычисление баллистических элементов
// calc(тип снаряда)
// см с[] в const.h
//-----------------------------------------------------------------------
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
    integrate(ksi, D, 0.001);
    //std::cout << "U: " << get_U() << '\n';
    //std::cout << "P: " << get_P() << '\n';
    //std::cout << "t: " << get_t() << '\n';
    //std::cout << "nu: " << get_nu() << '\n';
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
    return pow(1 + Lambda / T_N0 * calc_yG(y), -g_0 / (R_0 * Lambda) - 1);
}

//-----------------------------------------------------------------------
// Вычисление температуры на высоте y в кельвинах
// calc_T(высота)
//-----------------------------------------------------------------------
float Ballistic::calc_T(float y)
{
    return T_N0 + Lambda * calc_yG(y);
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
// integrate(начало, конец, шаг)
//-----------------------------------------------------------------------
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

    //std::ofstream fout("out.txt");
    //fout << 'x' << ';' << 'U' << ';' << 'P' << ';' << 't' << ';' << "nu" << '\n';
    for (int i = ksi; i < c; i++)
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

        a_p = nu / D * cos(D2R(eps));
        teta = a_p + eps;
        y = alt + ksi * sin(D2R(teta)) - nu;
        v = U * sqrt(1 + pow(P, 2) - 2 * P * sin(D2R(teta)));
        //fout << x << ';' << U << ';' << P << ';' << t << ';' << nu << '\n';
        x += h;
    }
    psi = atan2(t * W[1], D);
    //fout.close();
    return;
}

//-----------------------------------------------------------------------
// Линейный интерполятор
//-----------------------------------------------------------------------
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
