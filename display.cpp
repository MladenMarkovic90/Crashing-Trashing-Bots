/*
    Crashing Trashing Bots is a 3D game in freeglutcpp
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


/* klasa koja sluzi za prikaz sadrzaja prozora */


/* ukljucivanje potrebnih zaglavlja */
#include <iostream>
#include "global.h"
#include <cmath>
#include <cassert> // za debagovanje
#include "glutcpp/glutReshapeListener.h"
#include "glutcpp/glutAnimationTimer.h"
#include "robot.h"
#include "robot_1.h"
#include "robot_2.h"
#include "robot_3.h"
#include "glutcpp/glutLoadPicture.h"


using namespace std;


/* prikazuje sadrzaj prozora */
void Display::show(void)
{
    if(status.modus==MODUS_MENI)
	Display::meni();
    else if(status.modus==MODUS_START)
	Display::start();
    else if(status.modus==MODUS_ARENA)
        Display::arena();
     glutcpp::swapBuffers();

}


void Display::paused()
{
    int width=glutReshapeListenerInit::getReshapeListener()->getWindowWidth();
    int height=glutReshapeListenerInit::getReshapeListener()->getWindowHeight();

    glutcpp::screenDisplayBegin3D();

    glutcpp::color(0,0,0,0.9);
    glutcpp::pravougaonik(Tacka(1,1,0),Tacka(-1,1,0),Tacka(-1,-1,0),Tacka(1,-1,0));

    glutcpp::color(1,1,1,1);
    if(status.position==1) {
        glutcpp::color(1,1,0,1);
    }

    if(status.finished==false)
        glutcpp::text(((width-2*12)/(float)width)-1.0,-0.1,"EXIT");
    else
        glutcpp::text(((width-2*12)/(float)width)-1.0,0,"EXIT");
    
    glutcpp::color(1.0,1.0,1.0,1.0);
    if(status.position==0) {
        glutcpp::color(1.0,1.0,0.0,1.0);
    }
    if(status.finished==false)
        glutcpp::text(((width-4*12)/(float)width)-1.0,0.1,"CONTINUE");

    glutcpp::screenDisplayEnd3D(45,width,height,1,1000);

}


/* prikazuje meni */
void Display::meni()
{
    float width=glutReshapeListenerInit::getReshapeListener()->getWindowWidth();
    width=width/2;
    glutcpp::light(GL_OFF);
    glutcpp::modelView2D();

    glutLoadPicture::texture_display(Tacka(-1,-1,0),Tacka(1,-1,0),Tacka(1,1,0),Tacka(-1,1,0),PICTURE_MENI);
    glutcpp::color(0,0,0,1);
    glutcpp::text(((width-11*12)/width)-1.0,0.9,"CRASHING TRASHING BOTS");

    if(status.position==0)
        glutcpp::color(1,1,0,1);
    else
        glutcpp::color(0,0,0,1);
    glutcpp::text(((width-2*12)/width)-1.0,0.1,"PLAY");

    if(status.position==0)
        glutcpp::color(0,0,0,1);
    else
        glutcpp::color(1,1,0,1);
    glutcpp::text(((width-2*12)/width)-1.0,-0.1,"EXIT");
}


/* prikazuje meni->start */
void Display::start()
{
    status.ugao++;

    glutcpp::light(GL_ON);
    glutcpp::lightPosition(0,0,0,1);
    glutcpp::modelView3D(0,0,200);

    Robot * r;
    int ticksPerSecond=glutAnimationTimerInit::getAnimationTimer()->getTicksPerSecond();

    if(status.position%3==0)
    {
        r=new Robot_1(ticksPerSecond,PLAYER_1,Tacka(0,0,0));
    }
    else if(status.position%3==1)
    {
        r=new Robot_2(ticksPerSecond,PLAYER_1,Tacka(0,0,0));
    }
    else
        r=new Robot_3(ticksPerSecond,PLAYER_1,Tacka(0,0,0));

    glutcpp::translate(0,-20,-50);
    //glutcpp::rotate(0,1,0,0);
    glutcpp::rotate(-90,0,1,0);
    glutcpp::rotate(status.ugao,0,1,0);
    r->draw();
    delete r;

    glutcpp::color(1,1,1,1);
    glutcpp::screenDisplayBegin3D();
    glutcpp::begin(GL_TRIANGLES);
        glutcpp::vertex(0.9,0,0);
        glutcpp::vertex(0.8,0.1,0);
        glutcpp::vertex(0.8,-0.1,0);
    glutcpp::end();

    glutcpp::begin(GL_TRIANGLES);
        glutcpp::vertex(-0.9,0,0);
        glutcpp::vertex(-0.8,0.1,0);
        glutcpp::vertex(-0.8,-0.1,0);
    glutcpp::end();

    int width=glutReshapeListenerInit::getReshapeListener()->getWindowWidth();
    int height=glutReshapeListenerInit::getReshapeListener()->getWindowHeight();

    if(status.flag==PLAYER_1)
        glutcpp::text(((width-4*12)/(float)width)-1.0,0.9,"PLAYER 1");
    else
        glutcpp::text(((width-4*12)/(float)width)-1.0,0.9,"PLAYER 2");

    glutcpp::screenDisplayEnd3D(45,width,height,1,1000);

}


/* prikazuje arena */
void Display::arena()
{
    //this->camera_ugao+=0.1;
    glutcpp::light(GL_ON);

    glutcpp::modelView3D(0,0,200);

    glutcpp::color(0,1.0,0,1.0);
    glutcpp::lightPosition(0,0,0,1);


    adjust_camera();

    Delovi::podloga(400);

    for(Prepreka * item : prepreke)
        item->draw();
    for(Prepreka * item : prepreke)
        item->testDraw(0);


    for(Robot * item : roboti)
	item->draw();

    for(Robot * item : roboti)
        item->testDraw(20);


    int width=glutReshapeListenerInit::getReshapeListener()->getWindowWidth();
    int height=glutReshapeListenerInit::getReshapeListener()->getWindowHeight();

    for(Robot * item : roboti)
        item->display3D(45,width,height,1,1000);

    if(status.paused==true || status.finished==true)
	Display::paused();
}


/* funkcija za namestanje kamere */
void Display::adjust_camera()
{
    //cout << "ulazim u kamera metodu" << endl;
    Tacka oko(0,0,0);
    Tacka fokus(0,0,0);

    //da prikazuje iza ledja    
    if (roboti.size() == 1) {
	Robot *robot = roboti.back();
	assert(robot);
	fokus = robot->getPos();


        this->camera_ugao=(float)robot->getUgao();


	//nemam pojma zasto moram da dodam PI/2, nastelao sam ga
        oko.set_x(cam_dist * std::cos(this->camera_ugao/180*M_PI + M_PI_2) + fokus.get_x());
	oko.set_y(cam_dist);
        oko.set_z(cam_dist * std::sin(this->camera_ugao/180*M_PI + M_PI_2)  + fokus.get_z());
    }

    //TODO: specijalno za dva, mozda dodati posebno za vise ako bude potrebno
    if (roboti.size() >= 2) {
	Tacka prvi = roboti[0]->getPos();
	Tacka drugi = roboti[1]->getPos();
    	Tacka sredina = (prvi + drugi) / 2.0f;
	fokus = sredina;

	// projekcija kamere na xz ravan
	float dx = prvi.get_x() - sredina.get_x();
	float dz = prvi.get_z() - sredina.get_z();

	//imamo dve pozicije kandidate
	Tacka podnozje1 = sredina - Tacka(dz, 0, -dx);
	Tacka podnozje2 = sredina + Tacka(dz, 0, -dx);

	//biramo onu koja je dalja od sredine, kako bi gledala ka sredini (norma vektora)
	Tacka podnozje = podnozje1.norm() > podnozje2.norm() ? podnozje1 : podnozje2;

        float ugao_paused=this->camera_ugao;

        if(podnozje==podnozje1 && this->camera_indikator==NO_SWAP && this->camera_ugao>0)
            this->camera_ugao-=0.1;
        else if(podnozje==podnozje1 && this->camera_indikator==SWAP)
        {
            //this->camera_ugao=this->camera_ugao-180;
            this->camera_indikator=NO_SWAP;
        }
        else if(podnozje==podnozje2 && this->camera_indikator==SWAP && this->camera_ugao<360)
            this->camera_ugao+=0.1;
        else if(podnozje==podnozje2 && this->camera_indikator==NO_SWAP)
        {
            //this->camera_ugao=180-this->camera_ugao;
            this->camera_indikator=SWAP;
        }

        if(status.paused==true)
            this->camera_ugao=ugao_paused;

        if(status.paused==false)
            this->cam_position=this->cam_position+(this->cam_position.vek(podnozje1)/10);


        oko.set_x(this->cam_position.get_x()*std::sin(this->camera_ugao/180.0*M_PI));
        oko.set_y(0.7*prvi.distance(drugi)+10); //konstanta je nasumicna, kako mi se svidi
        oko.set_z(this->cam_position.get_z()*std::cos(-this->camera_ugao/180.0*M_PI));
    }
    
    //cout << "camera :" << this->camera_ugao << endl;
    //cout << oko.get_x() << " " << oko.get_y() << "" << oko.get_z() << endl;
    glutcpp::lookAt(oko, fokus);
    
}
