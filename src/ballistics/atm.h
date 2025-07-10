#ifndef ATM_H
#define ATM_H

#include <math.h>
#include "src/math/linal.h"

class atm
{
public:
    atm();

    float get_a(float H);  // Calc speed ​​of sound
    float get_ro(float H); // Calc air density
    float get_g(float H);  // Get gravitational acceleration
    float H_to_h(float H); // Transformation of geopotential height H into geometric height h
    float get_T(float H);  // Calc temperature
    float get_P(float H);  // Atmospheric pressure at a given altitude H

    float get_ro_N0() { return ro_N0; }

    float P_to_h(float P);

    // Закон изменения g(y) СА-81
    float g(float y);
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

};

#endif // ATM_H
