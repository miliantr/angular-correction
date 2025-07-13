#include "model.h"

Model::Model()
{

}

void Model::set_target(TVector coord)
{
    tCrd = coord;
    return;
}

void Model::set_machine(TVector coord)
{
    mCrd = coord;
    return;
}

void Model::set_sensor(float wind_speed, TVector wind_direction,
                float humidity, float temperature,
                float atmospheric_pressure, float rainfall)
{
    wSpd = wind_speed;
    wDir = wind_direction;
    hum = humidity;
    temp = temperature;
    atmPres = atmospheric_pressure;
    rain = rainfall;
    return;
}

void Model::set_Cord_ang(TVector ang)
{
    CAng = ang;
    return;
}

void Model::calc()
{
    calc_dist();
    calc_eps();
    calc_psi();
    return;
}

void Model::calc_dist()
{
    TVector d2(3);
    d2[0] = pow(tCrd[0] - mCrd[0], 2);
    d2[1] = pow(tCrd[1] - mCrd[1], 2);
    d2[2] = pow(tCrd[2] - mCrd[2], 2);
    D = sqrt(d2[0] + d2[1] + d2[2]);
    return;
}

void Model::calc_eps()
{
    eps = atan2(pow(tCrd[1] - mCrd[1], 2), pow(tCrd[0] - mCrd[0], 2));
    return;
}

void Model::calc_psi()
{
    psi = atan2(pow(tCrd[2] - mCrd[2], 2), pow(tCrd[0] - mCrd[0], 2));
    return;
}
