#include "mothership.h"
#include<iostream>
#include<allegro5/allegro.h>

using namespace std;
const int SCREEN_W = 800;
const int SCREEN_H = 800;
enum DIRECTIONS { 
	UP, DOWN, LEFT, RIGHT
};
AlienShip::AlienShip(int x, int y, ALLEGRO_BITMAP* pic)
{
	xpos = 0;
	ypos = 0;
	health = 0;
	xdir = 0;
	ydir = 0;
	image = pic;
}

void AlienShip::move()
{
	if (xdir == 1) //1 means right 
		xpos++;
	if (xdir == 1 && xpos > SCREEN_W - 60) //you can replace screen_w with the width of your screen 
		xdir = 0; //0 means left 
	if (xdir == 0) //1 means right  
		xpos--;
	if (xdir == 0 && xpos < 0) //you can replace screen_w with the width of your screen // 
		xdir = 1; //0 means left


	/////vertical movement//////
	if (ydir == 0) //1 means right
		ypos++;
	if (ydir == 1 && ypos > SCREEN_H - 100) //you can replace screen_w with the width of your screen
		ydir = 0; //0 means left
	if (ydir == 0) //1 means right
		ypos--;
	if (ydir == 0 && ypos < 0) //you can replace screen_w with the width of your screen
		ydir = 1; //0 means left
}

void AlienShip::draw()
{
	//int i = 0; int j = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			al_draw_bitmap_region(image, i * 80, j * 85, 80, 85, xpos, ypos, NULL);
		}
	}
}


void AlienShip::decreaseHealth()
{
	health -= 1;
}

int AlienShip::getX() {

	return xpos;
};
int AlienShip::getY() {

	return ypos;
};
int AlienShip::getHealth() {
	return health;
};