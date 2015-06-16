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


/* Ukljucujemo sve potrebna zaglavlja */
#include <vector>
#include <ctime>
#include "glutcpp/tacka.h"

#include "glutcpp/glutcpp.h"
#include "motionListener.h"
#include "mouseListener.h"
#include "reshapeListener.h"
#include "animationTimer.h"
#include "specialKeyListener.h"
#include "normalKeyListener.h"
#include "display.h"

#include "robot.h"
#include "robot_1.h"
#include "robot_2.h"
#include "robot_3.h"

#include "vektor3d.h"

#include "glutcpp/glutLoadPicture.h"


int main(int argc,char ** argv)
{

    /* status za moduse */
    animationStatus status;
    status.modus=MODUS_MENI;
    //status.modus=MODUS_ARENA;

    /* vektor za sve robotice */
    std::vector<Robot *> roboti;

    /* inicijalizujemo random sa semenom */
    /* potrebno za animacije */
    std::srand(time(NULL));

    /* Inicalizujemo glut */
    glutcpp::init(argc,argv,600,600,"Crashing Trashing Bots");

    /* Inicijalizujemo glut niti */
    glutDisplayInit::run(new Display(roboti,status));
    glutAnimationTimerInit::run(new animationTimer(50,roboti,status));
    glutNormalKeyListenerInit::run(new normalKeyListener(roboti,status));
    glutSpecialKeyListenerInit::run(new SpecialKeyListener(roboti,status));
    glutReshapeListenerInit::run(new reshapeListener(600,600,status));

    float ticksPerSecond=glutAnimationTimerInit::getAnimationTimer()->getTicksPerSecond();


    /* BITNO -> PUTANJA MORA BITI TACNA */
    glutLoadPicture::load("slike/meni.bmp",PICTURE_MENI);

    glutcpp::fullScreen();

    /* Pokrecemo glut petlju */
    glutcpp::start();

    return 0;
}
