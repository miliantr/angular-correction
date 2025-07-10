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

    float euler(float x0, float xf, float h);

private:
    const float altitude = 170.0; // Средняя высота по Восточно-Европейской равнине
    TVector w;

    float eps = 30; // Угол места цели
    float a_p = 0; // Угловая поправка

    float ksi = 0;
    float D_y = 2000;

    float linearInterpolate(const float table[][2], float X);
    float H(float y);
    float get_E(float h, float v, int bullet);
};

#endif // BALL_H
