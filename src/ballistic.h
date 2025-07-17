//-----------------------------------------------------------------------
//  Source      : ballistic.h
//  Created     : 03.07.2025
//  Modified    : 17.07.2025
//  Author      : MD Vladislav
//-----------------------------------------------------------------------

#ifndef BALLISTIC_H
#define BALLISTIC_H

#include <math.h>

#include "src/linal.h"
#include "src/const.h"

//-----------------------------------------------------------------------

using namespace LinearAlgebra;

//-----------------------------------------------------------------------

class Ballistic
{
public:
    Ballistic();

    // Начальные условия
    void set_cond(float distanse, float eps_, float U_,
                  float U_speed, float altitude);

    // Вычисление баллистических элементов
    void calc(int type);

    // Геттер угловой поправки (угол между линией стрельбы и линией визирования) [рад]
    float get_a_p() { return a_p; }

    // Геттер угла по 0Y (угол между линией стрельбы и относом за счет ветра и деривации) [рад]
    float get_psi() { return psi; }

    // Геттер угал бросания (угол между горизонтом и линией стрельбы) [рад]
    float get_teta() { return teta; }

private:
    // Основыные характеристики СА-81
    const float R_E = 6356767.0;    // Радиус Земли
    const float g_0 = 9.80665;      // Ускорение силы тяжести
    const float ro_N0 = 1.225;      // Плотность воздуха
    const float T_N0 = 288.15;      // Температура воздуха
    const float R_0 = 287.05287;    // Удельная газовая постоянная
    const float Lambda = -0.0065;   // Градиент температуры
    //const float k = 1.44;           // Показатель адиабаты
    //const float a_N0 = 340.294;
    //const float P_N0 = 101325;

    // Const
    //const float MC = 28.964420;     // Molar mass of dry air
    const float Rk = 20.046796;     // R * k
    const float   reziba = 0.254;   // Шаг нарезов

    int     bType;      // Тип снаряда
    float   tab[79][2]; // Мат. таблица сопротивления

    float   alt;    // Высота начала стрельбы
    float   D;      // Дальность стрельбы
    float   eps;    // Угол места цели
    float   psi;    // Угол по 0Y (угол между линией стрельбы и относом за счет ветра и деривации)
    TVector W;      // Путевая скорость снаярда
    float   teta;   // Угол бросания (угол между горизонтом и линией стрельбы)
    float   a_p;    // Угловая поправка (угол между линией стрельбы и линией визирования)
    float   om;     // Угловая скорость вращения пули
    float   derivation;

    float interpolate(const float table[][2], float X, float Y);
    void  integrate(float xf, float h);

    float calc_H(float y);
    float calc_T(float y);
    float calc_a(float y);
    float calc_yG(float y);
    float calc_g(float y);
    float calc_M(float veol, float altitude);
    float calc_E(float y, float veol);
    float calc_om(float veol);
    float clac_magnus(float veol);
    float clac_der(float veol, float time);
    float get_omega() {return om; }
};

#endif // BALLISTIC_H
