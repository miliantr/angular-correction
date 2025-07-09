#include "src/math/linal.h"
#include "src/ballistics/atm.h"

#include <iostream>

using namespace LinearAlgebra;

int main()
{
    atm atm1;
    float H;

    H = 100.0;
    std::cout << H << '\n';
    std::cout << atm1.get_a(H) << '\n';
    std::cout << atm1.get_g() << '\n';
    std::cout << atm1.get_P(H) << '\n';
    std::cout << atm1.get_ro(H) << '\n';
    std::cout << atm1.get_T(H) << '\n';
    std::cout << atm1.H_to_h(H) << '\n';

    std::cout << '\n';

    H = 800.0;
    std::cout << H << '\n';
    std::cout << atm1.get_a(H) << '\n';
    std::cout << atm1.get_g() << '\n';
    std::cout << atm1.get_P(H) << '\n';
    std::cout << atm1.get_ro(H) << '\n';
    std::cout << atm1.get_T(H) << '\n';
    std::cout << atm1.H_to_h(H) << '\n';
    return 0;
}
