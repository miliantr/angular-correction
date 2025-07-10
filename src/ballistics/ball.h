#ifndef BALL_H
#define BALL_H

#include "src/ballistics/const.h"
#include "src/ballistics/atm.h"

using namespace LinearAlgebra;

class ball
{
public:
    ball(TVector v_, TVector u_);
    atm atm1;
    float get_E();

private:
    float h = 170.0; // Средняя высота по Восточно-Европейской равнине
    TVector v;
    TVector u;
    TVector w;
    float H(float y);
    float lagranjInterpolate(const float table[][2],float X); // fix needed
    float linearInterpolate(const float table[][2], float X);
};

#endif // BALL_H
