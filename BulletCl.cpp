#include "BulletCl.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include<iostream>

using namespace std;

BulletClass::BulletClass(int x, int y)
{
	xPos = x;
	yPos = y;
	angle = 0;
	radius = 10;
	Alive = 0;
}

void BulletClass::move()
{
	angle += .10;
	xPos = xPos + cos(angle);
	yPos++;
	yPos++;
}

void BulletClass::draw()
{
	if (Alive == true) {
		//al_draw_bitmap_region(image, i * 80, j * 85, 80, 85, xPos, yPos, NULL);
		al_draw_filled_circle(xPos, yPos, 60, al_map_rgb(200, rand()%250, 45));
		//cout << "drawing at "<<xPos<<" "<<yPos << endl;
	}
}

void BulletClass::kill()
{
	Alive = false;
}

bool BulletClass::offScreen()
{
	if (yPos >1000) {
		return true;
	}
	else
		return false;
}

bool BulletClass::isAlive()
{
	return Alive == true;
}

int BulletClass::getx()
{
	return xPos;
}

int BulletClass::gety()
{
	return yPos;
}

void BulletClass::shoot(int x, int y)
{
	//cout << "shoot.";
	Alive = true;
	xPos = x + 16;
	yPos = y;
	//cout << "bullet is at " << xPos << " , " << yPos << endl;
}

bool BulletClass::collide(double x, double y)
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

BulletClass::BulletClass()
{
}


