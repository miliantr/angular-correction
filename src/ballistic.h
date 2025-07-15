#ifndef BALLISTIC_H
#define BALLISTIC_H

#include <math.h>

#include "src/linal.h"
#include "src/const.h"

using namespace LinearAlgebra;

class Ballistic
{
public:
    Ballistic();

    void set_cond(float distanse, float eps_, float U_,
                  float U_speed, float altitude);

    void calc(int type);

    float get_a_p() { return a_p; }
    float get_psi() { return psi; }
    float get_teta() { return teta; }

    float get_U() { return U;}
    float get_P() { return P;}
    float get_t() { return t;}
    float get_nu() { return nu;}

private:
    // Основыные характеристики СА-81
    const float R_E = 6356767.0; // Радиус Земли
    const float g_0 = 9.80665; // Ускорение силы тяжести
    const float ro_N0 = 1.225; // Плотность воздуха
    const float T_N0 = 288.15; // Температура воздуха
    //const float k = 1.44; // Показатель адиабаты
    const float R_0 = 287.05287; // Удельная газовая постоянная
    const float Lambda = -0.0065; // Градиент температуры
    //const float a_N0 = 340.294;
    //const float P_N0 = 101325;

    // Const
    const float Rk = 20.046796; // R * k
    //const float MC = 28.964420; // Molar mass of dry air

    float ksi = 0.0;

    float alt; // Высота начала стрельбы
    float D; // Дальность стрельбы
    float eps; // Угол места цели
    float psi; // Угол по 0Y
    TVector W; // Путевая скорость снаярда
    TVector CAng;
    float U;
    float P;
    float t;
    float nu; // Понижение снаряда
    float teta; // Угол бросания
    float a_p; // Уголовая поправка
    int bType; // Тип снаряда
    float tab[79][2]; // Мат. таблица сопротивления

    float interpolate(const float table[][2], float X, float Y);
    void integrate(float x0, float xf, float h);

    float calc_H(float y);
    float calc_T(float y);
    float calc_a(float y);
    float calc_yG(float y);
    float calc_g(float y);
    float calc_M(float veol, float altitude);
    float calc_E(float y, float veol);
};

#endif // BALLISTIC_H
