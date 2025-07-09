#include <iostream>

#include "src/math/linal.h"
#include "src/ballistics/atm.h"
#include "src/ballistics/const.h"
#include "src/math/interpolation.h"

using namespace LinearAlgebra;

int main()
{
    std::cout << interpolate(500.0) << '\n';

    //atm atm1;
    //float H;
    //H = 100.0;
    //std::cout << H << '\n';
    //std::cout << atm1.get_a(H) << '\n';
    //std::cout << atm1.get_g() << '\n';
    //std::cout << atm1.get_P(H) << '\n';
    //std::cout << atm1.get_ro(H) << '\n';
    //std::cout << atm1.get_T(H) << '\n';
    //std::cout << atm1.H_to_h(H) << '\n';
    //std::cout << '\n';
    //H = 800.0;
    //std::cout << H << '\n';
    //std::cout << atm1.get_a(H) << '\n';
    //std::cout << atm1.get_g() << '\n';
    //std::cout << atm1.get_P(H) << '\n';
    //std::cout << atm1.get_ro(H) << '\n';
    //std::cout << atm1.get_T(H) << '\n';
    //std::cout << atm1.H_to_h(H) << '\n';
    return 0;
}
