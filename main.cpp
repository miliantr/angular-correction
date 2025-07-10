#include <iostream>

#include "src/ballistics/ball.h"

int main()
{
    TVector v(3); // Скорость снаряда
    v[0] = 840.0;
    TVector u(3); // Скорость ветра
    u[0] = 3.0;

    ball ball1(v, u);

    std::cout << ball1.get_E() << '\n';

    return 0;
}
