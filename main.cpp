#include <iostream>

#include "src/ballistics/ball.h"

//#include "src/math/linal.h"
//#include "src/ballistics/atm.h"
//#include "src/ballistics/const.h"
//#include "src/math/interpolation.h"

//using namespace LinearAlgebra;

int main()
{
    ball ball1;
    std::cout << ball1.get_E(840) << '\n';

    //std::cout << LagranjInterpol(G7, 840.0) << '\n' << LinearInterpol(G7, 840.0);

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
