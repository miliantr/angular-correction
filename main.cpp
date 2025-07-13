#include <iostream>

#include "src/model.h"
#include "src/ballistic.h"

int main()
{
    Model model;

    TVector wd(3);
    wd[0] = 1.0;
    wd[1] = 0.0;
    wd[2] = 0.0;
    model.set_sensor(3.0, wd, 10.0, 10.0, 100000.0, 2.0);

    TVector tc(3);
    tc[0] = 5000.0;
    tc[1] = 190.0;
    tc[2] = 30.0;
    model.set_target(tc);

    TVector mc(3);
    mc[0] = 10.0;
    mc[1] = 170.0;
    mc[2] = 20.0;
    model.set_machine(mc);

    TVector Cang(2);
    mc[0] = 0.0;
    mc[1] = 0.0;
    model.set_Cord_ang(Cang);

    model.calc();

    Ballistic ball;

    TVector v01(3);
    v01[0] = 850;
    v01[1] = 0;
    v01[2] = 0;

    ball.set_cond(model.get_distance(), model.get_eps(),
                  v01, model.get_wind_direction(), model.get_wind_speed(),
                  model.get_Cord_ang(), model.get_machine()[1]);
    ball.calc(1);
    std::cout << "Angular corr: " << ball.get_a_p() << '\n';
    return 0;
}
