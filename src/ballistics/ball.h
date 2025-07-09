#ifndef BALL_H
#define BALL_H

#include "src/math/linal.h"
#include "src/ballistics/atm.h"
#include "src/ballistics/const.h"
//#include "src/math/interpolation.h"

class ball
{
public:
    ball();
    atm atm1;
    float get_E(float v);

private:
    float h = 170.0; // Средняя высота по Восточно-Европейской равнине
    float H(float y);
    const double M_PI = 3.14159265358979323846;
};

#endif // BALL_H
