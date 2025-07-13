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

    void set_cond(float distanse, float eps_, TVector v,
                   TVector u, TVector Cord_angle, float altitude);

    void calc(int type);
    void calc_a_p();

    float get_U() { return U;}
    float get_P() { return P;}
    float get_t() { return t;}
    float get_nu() { return nu;}

private:
    // Основыные характеристики СА-81
    const float R_E = 6356767.0; // Earth radius
    const float g_0 = 9.80665;
    const float ro_N0 = 1.225;
    const float T_N0 = 288.15;
    const float k = 1.44;
    const float R_0 = 287.05287;
    const float Lambda = -0.0065; // Vertical temperature gradient
    const float a_N0 = 340.294;
    const float P_N0 = 101325;

    // Const
    const float Rk = 20.046796; // R * k
    const float MC = 28.964420; // Molar mass of dry air

    float alt = 0;
    float ksi = 0;
    float D = 0;
    float eps = 0;
    TVector W;
    TVector CAng;
    float U = 0;
    float P = 0;
    float t = 0;
    float nu = 0;
    float teta = 0;
    float a_p = 0;
    int bType = 0;
    float tab[79][2];

    float interpolate(const float table[][2], float X, float Y);
    void integrate(float x0, float xf, float h);

    float calc_E(float y, TVector veol);
    float calc_H(float y);
    float calc_T(float y);
    float calc_a(float y);
    float calc_yG(float y);
    float calc_g(float y);
    float calc_M(float veol, float altitude);
};

#endif // BALLISTIC_H
