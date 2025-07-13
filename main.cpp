#include <iostream>

#include "src/model.h"
#include "src/ballistic.h"

int main()
{
    Model model;

    TVector wd(3);
    wd[0] = 1;
    wd[1] = 0;
    wd[2] = 0;
    model.set_sensor(3, wd, 10, 10, 99590, 0);

    TVector tc(3);
    tc[0] = 100.0;
    tc[1] = 100.0;
    tc[2] = 100.0;
    model.set_target(tc);

    TVector mc(3);
    mc[0] = 0.0;
    mc[1] = 0.0;
    mc[2] = 0.0;
    model.set_machine(mc);

    model.calc();

    Ballistic ball;

    TVector v01(3);
    v01[0] = 840;
    v01[1] = 0;
    v01[2] = 0;

    ball.set_cond(model.get_distance(), model.get_eps(),
                  v01, model.get_wind_direction(),
                  model.get_Cord_ang(), model.get_machine()[1]);
    ball.calc(1);

    std::cout << ball.get_nu();
    return 0;
}
