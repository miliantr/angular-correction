#include "atm.h"

atm::atm()
{

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

float atm::get_g()
{
    return GC;
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
