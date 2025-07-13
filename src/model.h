#ifndef MODEL_H
#define MODEL_H

#include <math.h>

#include "src/linal.h"

using namespace LinearAlgebra;

class Model
{
public:
    Model();

    void set_target(TVector coord);
    void set_machine(TVector coord);
    void set_sensor(float wind_speed, TVector wind_direction,
                    float humidity, float temperature,
                    float atmospheric_pressure, float rainfall);
    void set_Cord_ang(TVector ang);

    void calc();

    TVector get_target() { return tCrd; }
    TVector get_machine() { return mCrd; }
    TVector get_wind_direction() { return wDir; }
    TVector get_Cord_ang() { return CAng; }
    float   get_wind_speed() { return wSpd; }
    float   get_humidity() { return hum; }
    float   get_temperature() { return temp; }
    float   get_atmospheric_pressure() { return atmPres; }
    float   get_rainfall() { return rain; }
    float   get_distance() { return D; }
    float   get_eps() { return eps; }
    float   get_psi() { return psi; }

private:
    TVector tCrd;
    TVector mCrd;
    TVector CAng;
    TVector wDir;
    float   wSpd = 0;
    float   hum = 0;
    float   temp = 0;
    float   atmPres = 0;
    float   rain = 0;
    float   D = 0;
    float   eps = 0;
    float   psi = 0;

    void calc_dist();
    void calc_eps();
    void calc_psi();
};

#endif // MODEL_H
