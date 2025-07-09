#ifndef ATM_H
#define ATM_H

#include <math.h>

#define gradToKelvin (T) (T * (-273.15))

class atm
{
public:
    atm();

    float get_a(float H);   // Calc speed ​​of sound
    float get_ro(float H);  // Calc air density
    float get_g(float H);   // Get gravitational acceleration
    float H_to_h(float H);  // Transformation of geopotential height H into geometric height h
    float get_T(float H);   // Calc temperature
    float get_P(float H);   // Atmospheric pressure at a given altitude H

    float get_ro_n0() { return ro_N0; }

    float P_to_h(float P);

    // Закон изменения g(y) СА-81
    float g(float y);
private:
    // Const
    float RE = 6356767.0;   // Erath radius
    float GC = 9.80665;     // Gravitational acceleration
    float MC = 28.964420;   // Molar mass of dry air
    float R = 287.05287;    // Gas constant for air
    float BETTA = -0.0065;  // Vertical temperature gradient
    float K = 20.046796;    // R * 1.44

    float T_0 = 288.15;     // Temperature in kelvin
    float P_0 = 101325.0;   // Pressure
    float a;                // Speed ​​of sound

    // Эталонные значения СА-81
    float R_E = 6356767.0;
    float g_0 = 9.80665;
    float ro_N0 = 1.225;
    float T_N0 = 288.15;
    float k = 1.44;
    float R_0 = 287.053;
    float a_N0 = 340.294;
    float P_N0 = 101325;
};

#endif // ATM_H
