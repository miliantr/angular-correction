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
    return (P - P_0) / (1 * GC);
}

float atm::get_a(float H)
{
    return K * sqrt(get_T(H));
}

float atm::get_T(float H)
{
    H = H_to_h(H);
    return this->T_0 + this->BETTA * H;
}

float atm::H_to_h(float H)
{
    return (RE * H) / (RE + H);
}

float atm::get_g(float H)
{
    return GC * pow(RE / (RE + H), 2);
}

float atm::get_P(float H)
{
    float T = get_T(H);
    return P_0 * pow(T / T_0, (GC * MC) / (R * BETTA));
}

float atm::get_ro(float H){
    float P = get_P(H);
    float T = get_T(H);
    return (P * MC) / (R * T);
}
