#include "atm.h"

atm::atm()
{

}

float atm::g(float y)
{
    return g_0 * pow(R_E / (R_E + y), 2);
}

float atm::P_to_h(float P)
{
    return (P - P_N0) / (1 * g_0);
}

float atm::get_a(float H)
{
    return Rk * sqrt(get_T(H));
}

float atm::get_T(float H)
{
    H = H_to_h(H);
    return this->T_N0 + this->Lambda * H;
}

float atm::H_to_h(float H)
{
    return (R_E * H) / (R_E + H);
}

float atm::get_g(float H)
{
    return g_0 * pow(R_E / (R_E + H), 2);
}

float atm::get_P(float H)
{
    float T = get_T(H);
    return P_N0 * pow(T / T_N0, (g_0 * MC) / (R_0 * Lambda));
}

float atm::get_ro(float H){
    float P = get_P(H);
    float T = get_T(H);
    return (P * MC) / (R_0 * T);
}
