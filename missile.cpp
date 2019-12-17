#include "missile.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include<iostream>

using namespace std;

MissileClass::MissileClass(int x, int y, ALLEGRO_BITMAP* pic)
{
	xPos = x;
	yPos = y;
	angle = 0;
	radius = 10;
	Alive = 0;
}

void MissileClass::move()
{
	yPos -= 15;
}

void MissileClass::draw()
{
	if (Alive == true) {
		//al_draw_bitmap_region(image, i * 80, j * 85, 80, 85, xPos, yPos, NULL);
		al_draw_filled_circle(xPos, yPos, 6, al_map_rgb(200, 30, 45));
	
	}
}

void MissileClass::kill()
{
	Alive = false;
}

bool MissileClass::offScreen()
{
	if (yPos < 0) {
		return true;
	}
	else
		return false;
}

bool MissileClass::isAlive()
{
	return Alive == true;
}

int MissileClass::getx()
{
	return xPos;
}

int MissileClass::gety()
{
	return yPos;
}

void MissileClass::shoot(int x, int y)
{
	Alive = true;
	xPos = x + 16;
	yPos = y;
}

bool MissileClass::collide(double x, double y)
{

	x = (x - xPos) * (x - xPos);
	y = (y - yPos) * (y - yPos);
	double dxy = sqrt(x + y);
	if (radius > dxy) {
		cout << "hit!";
		return true;
	}
	else
		return false;
}