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


/* Nadklasa za robotice i rad sa njim */


#ifndef ROBOT_H
#define ROBOT_H


/* Ukljucivanje potrebnih zaglavlja */
#include "tacka.h"
#include "timer.h"
#include <cmath>


/* Mora ponovo define, jer je u global posle includes zaglavlja */
/* PI define za Windows */
#ifndef M_PI
#define M_PI 3.14159265359
#endif
#ifndef M_PI_2
#define M_PI_2 M_PI/2.0
#endif


/* Razne definicije za lakse razumevanje koda */

/* Definicije konstanti za dugmad */
#define KEY_NONE 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4


/* Definicije konstanti za player */
#define PLAYER_NONE 0
#define PLAYER_1 1
#define PLAYER_2 2


class Robot
{
public:

    /* Konstruktor za Robot koji prima argument, za koji igrac se vezuje i gde se nalazi inicijalno u prostoru */
    Robot(int player=PLAYER_NONE,Tacka centar=Tacka(0,0,0),Tacka front=Tacka(0,0,0),float ugao=0,
          int cooldown1=5*SECOND,int cooldown2=5*SECOND,int cooldown3=5*SECOND,int cooldown4=5*SECOND);

    /* Funkcija za postavljanje flags za obicne karaktere, izvrsava se u klasi keys */
    void set_key(unsigned char key);

    /* Funkcija za skidanje flags za obicne karaktere, izvrsava se u klasi keys */
    void unset_key(unsigned char key);

    /* Funkcija za postavljanje flags za specijalne karaktere, izvrsava se u klasi special_keys */
    void set_key(int key);

    /* Funkcija za skidanje flags za specijalne karaktere, izvrsava se u klasi special_keys */
    void unset_key(int key);

    /* Animacija i izracunavanje za robotic, izvrsava se u klasi timer */
    virtual void animation();

    /* Iscrtavanje robotica, izvrsava se u klasi display */
    virtual void draw();

    /* Iscrtavanje podataka na povrsinu prozora, izvrsava se u klasi display */
    void display3D(int ugao,int width,int height,int arg1,int arg2);


    //TODO: PODESITI OSTALE PARAMETRE KASNIJE KADA BUDU NAPRAVLJENI
    void setUgao(float ugao) {_ugao=ugao;}
    void setPos(Tacka t) {_center=t;}
    //END TODO


    /* Getter za centar robotica */
    Tacka getPos() const { return _center; }

    /* Getter za ugao koji sluzi za rotaciju robotica */
    float getUgao() const { return _ugao; }

    /* Getter za player vezan za robotica */
    int getPlayer() const { return _player; }

    /* Getter za front tacku */
    Tacka getFront() const {
        Tacka tmp=Tacka(0,0,0);
        tmp.set_x(_front.get_x()*std::cos(-_ugao/180.0*M_PI)+_front.get_z()*std::sin(-_ugao/180.0*M_PI));
        tmp.set_z(_front.get_x()*std::sin(-_ugao/180.0*M_PI)+_front.get_z()*std::cos(-_ugao/180.0*M_PI));
        tmp.add(_center);
        return tmp;
    }
    
protected:

    /* Flag koji oznacava igraca */
    int _player;

    /* Flagovi za pravce koji su stisnuti */
    unsigned char _up_down;
    unsigned char _left_right;

    /* Centar robota */
    Tacka _center;

    /* Front (prednji deo) robota */
    Tacka _front;

    /* Ugao koji sluzi za rotaciju robotica */
    float _ugao;

    /* Privremena promenljiva za brzinu */
    float _speed=5;

    /* Promenljive/Flag za stanje abilitys */
    int _ability_1=0;
    int _ability_2=0;
    int _ability_3=0;
    int _ability_4=0;

    /* Promenljive koje oznacavaju cooldown od abilitys */
    int _ability_1_cooldown=5*SECOND;
    int _ability_2_cooldown=5*SECOND;
    int _ability_3_cooldown=5*SECOND;
    int _ability_4_cooldown=5*SECOND;
};

#endif // ROBOT_H
