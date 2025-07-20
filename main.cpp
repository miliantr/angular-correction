#include <iostream>

#include "src/model.h"
#include "src/ballistic.h"

int main()
{
    Model model;

    float wd = 45.0; // Направление ветра в градусах
    float ws = 3.0; // Скорость ветра
    model.set_sensor(ws, wd, 10.0, 300.0, 100000.0, 2.0);

    TVector tc(3);
    tc[0] = 4000.0;
    tc[1] = 0.0;
    tc[2] = 0.0;
    model.set_target(tc);

    TVector mc(3);
    mc[0] = 0.0;
    mc[1] = 0.0;
    mc[2] = 0.0;
    model.set_machine(mc);

    model.calc();

    Ballistic ball;

    ball.set_cond(model.get_distance(), model.get_eps(),
                  wd, model.get_wind_speed(),
                  model.get_machine()[1]);
    ball.calc(0);

    std::cout << "a_p: " << ball.get_a_p() << '\n';
    std::cout << "psi: " << ball.get_psi() << '\n';
    std::cout << "teta: " << ball.get_teta() << '\n';
    return 0;
}
