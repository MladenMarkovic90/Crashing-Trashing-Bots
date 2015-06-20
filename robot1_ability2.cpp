#include "robot1_ability2.h"

Robot1_ability2::Robot1_ability2()
{

}

Robot1_ability2::~Robot1_ability2()
{

}

Robot1_ability2::Draw()
{
    //NOTE: tacka udarca -> this->tacka_raketa + Tacka(20,0,0);
    /* RANGE ABILITY */
    /* Raketa */

    /* pozicija i ugao rakete */
    float number=0;
    if(this->_ability_2>0)
        number=5*_ticksPerSecond-this->_ability_2;
    else
    {
        this->ugao_raketa=this->_ugao-90;
        this->tacka_raketa_help=this->_center;
    }

    number*=10;
    this->tacka_raketa=Tacka(20,0,0)+Tacka(1,0,0)*number;

    glutcpp::push();
        /* postavljamo raketu na odredjeno mesto */
        glutcpp::translate(this->tacka_raketa_help);
        glutcpp::translate(0,5,0);

        glutcpp::rotate(-this->ugao_raketa,0,1,0);

        glutcpp::translate(tacka_raketa);
        glutcpp::translate(Tacka(-20,0,0));

        /* ako je number vece od 0, onda se raketa krece i izbacuje vatru */
        if(number>0)
        {
            glutcpp::color(1,0.5,0,0.5);
            for(int i=0;i<25;i++)
            {
                float x=((float)std::rand()/RAND_MAX)*5.0;
                float y=-3+((float)std::rand()/RAND_MAX)*6.0;
                float c=-1+((float)std::rand()/RAND_MAX)*2.0;
                glutcpp::linija(Tacka(-x,-y,0),Tacka(-(3+x),-(y+c),0));
            }
        }

        /* Raketa */
        glutcpp::rotate(90,0,1,0);
        glutcpp::color(0.5,0.5,0.5,1);
        glutcpp::cylinder(3,15);
        glutcpp::rotate(-90,0,1,0);
        glutcpp::translate(15,0,0);
        glutcpp::rotate(90,0,1,0);
        glutcpp::color(1,0,0,0.8);
        glutcpp::cone(5,6);

    glutcpp::pop();

    /*test*//*
    glutcpp::push();
        glutcpp::color(1,1,1,1);
        glutcpp::translate(provera::position(tacka_raketa,tacka_raketa_help,ugao_raketa));
        glutcpp::cube(5);
    glutcpp::pop();

    glutcpp::push();
        glutcpp::color(1,0,0,1);
        glutcpp::translate(_center);
        glutcpp::cube(5);
    glutcpp::pop();*/
}
