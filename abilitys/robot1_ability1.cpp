/*
    Crashing Trashing Bots is a 3D game in freeglut
    Copyright (C) 2015 Mladen Markovic,Tamara Plazinic,Nikola Banjac

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


/* Ukljucivanje potrebnih zaglavlja */
#include "ability.h"
#include "robot1_ability1.h"


/* konstruktor koji prima kolko dugo se ceka za sledece koriscenje,
 * kolko puta se iscrtava po sekundi */
Robot1_ability1::Robot1_ability1(int cooldown,int ticksPerSecond)
    : Ability(cooldown,ticksPerSecond,5 , Tacka(0,0,-30) )
{_damage=25;}


/* crtanje ability */
void Robot1_ability1::draw()
{
    /* MELEE ABILITY */
    /* Cekic */

    /* odredjivanje ugla cekica */
    float ugao_cekic=0;
    if(_time>4.5*_ticksPerSecond)
        {
        ugao_cekic=(_time - 4.5*_ticksPerSecond)*2;
        //std::cout << 1 <<std::endl;
        }
    else if(_time>2.5*_ticksPerSecond)
        ugao_cekic=(4.5*_ticksPerSecond - _time)/2;
        //std::cout << 2 <<std::endl;
    else
        ugao_cekic=_ticksPerSecond;
    ugao_cekic=ugao_cekic/_ticksPerSecond;

    glutcpp::push();
        /* namestanje cekica */
        glutcpp::translate(_center);
        glutcpp::rotate(-_ugao,0,1,0);
        glutcpp::rotate(90,0,1,0);
        glutcpp::translate(10,13,0);
        glutcpp::rotate(90*ugao_cekic,0,0,1);

        glutcpp::color(0.2,0.2,0.2,1);

        /* levi drzac cekica */
        glutcpp::push();
            glutcpp::translate(0,0,-15);
            glutcpp::kvadar(Tacka(-1,-1,0),Tacka(1,-1,0),Tacka(1,1,0),Tacka(-1,1,0),
                         Tacka(-1,-1,5),Tacka(1,-1,5),Tacka(1,1,5),Tacka(-1,1,5));
            glutcpp::kvadar(Tacka(-1,-1,-1),Tacka(-1,1,-1),Tacka(-1,1,1),Tacka(-1,-1,1),
                         Tacka(20,-1,-1),Tacka(20,1,-1),Tacka(20,1,1),Tacka(20,-1,1));
        glutcpp::pop();

        /* desni drzac cekica */
        glutcpp::push();
            glutcpp::translate(0,0,15);
            glutcpp::kvadar(Tacka(-1,-1,0),Tacka(1,-1,0),Tacka(1,1,0),Tacka(-1,1,0),
                         Tacka(-1,-1,-5),Tacka(1,-1,-5),Tacka(1,1,-5),Tacka(-1,1,-5));
            glutcpp::kvadar(Tacka(-1,-1,-1),Tacka(-1,1,-1),Tacka(-1,1,1),Tacka(-1,-1,1),
                         Tacka(20,-1,-1),Tacka(20,1,-1),Tacka(20,1,1),Tacka(20,-1,1));
        glutcpp::pop();

        /* donja kupa cekica */
        glutcpp::push();
            glutcpp::translate(20,-8,0);
            glutcpp::rotate(90,-1,0,0);
            glutcpp::cone(10,15);
        glutcpp::pop();

        /* gornja kupa cekica */
        glutcpp::push();
            glutcpp::translate(20,8,0);
            glutcpp::rotate(90,1,0,0);
            glutcpp::cone(10,15);
        glutcpp::pop();

        /* sipka koja prolazi kroz cekic */
        glutcpp::push();
            glutcpp::translate(19,0,0);
            glutcpp::kvadar(2,30,2);
        glutcpp::pop();

    glutcpp::pop();

    /* debug crtanje */
    testDraw();
}


/* dodatna izracunvanja za tacku sudara */
void Robot1_ability1::animation2(Tacka _centar_robota, float _ugao_robota)
{
    this->_center=_centar_robota;
    this->_ugao=_ugao_robota;
}
