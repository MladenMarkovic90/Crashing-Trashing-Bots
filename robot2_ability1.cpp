#include "robot2_ability1.h"

Robot2_ability1::Robot2_ability1()
{

}

Robot2_ability1::~Robot2_ability1()
{

}

Robot2_ability1::Draw()
{
    /* NOTE tacka udarca provera::position(tacka_kolac,_center,_ugao) */
    /* MELEE ABILITY */
    /* Kolac */

    /* promenljive za poziciju nozveva */
    float number=0;
    if(this->_ability_1>4*_ticksPerSecond)
        number=5*_ticksPerSecond-this->_ability_1;
    else if(this->_ability_1>3.5*_ticksPerSecond)
        number=_ticksPerSecond;
    else if(this->_ability_1>2.5*_ticksPerSecond)
        number=this->_ability_1 - 2.5*_ticksPerSecond;
    else
        number=0;
    number=number/_ticksPerSecond;

    number*=15;
    /* potrebno za koliziju */
    //this->tacka_kolac=this->_center+Tacka(0,0,-1)*number;
    this->tacka_kolac=Tacka(0,0,-15)+Tacka(0,0,-1)*number;

    if(number>-1)
    {
        glutcpp::push();
            /* postavljamo laser na odredjeno mesto */
            glutcpp::translate(_center);
            glutcpp::translate(0,5,0);

            glutcpp::rotate(-this->_ugao,0,1,0);
            glutcpp::translate(this->tacka_kolac);
            glutcpp::translate(Tacka(0,0,15));


            /* Laser */
            glutcpp::color(0.5,0.5,0.5,1);
            glutcpp::rotate(180,0,1,0);
            glutcpp::cone(3,15);

        glutcpp::pop();
    }

    /*test*//*
    glutcpp::push();
        glutcpp::color(1,1,1,1);
        glutcpp::translate(provera::position(tacka_kolac,_center,_ugao));
        glutcpp::cube(5);
    glutcpp::pop();*/
}
