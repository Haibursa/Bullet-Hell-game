#pragma once
#include<iostream>
#include<allegro5/allegro.h>
using namespace std;
class AlienShip {

private:
	double xpos;
	double ypos;
	int xdir;
	int ydir;
	int health;
	int cellNum = 0;
	ALLEGRO_BITMAP* image;
public:
	AlienShip(int x, int y, ALLEGRO_BITMAP* pic);
	void move();
	void draw();
	void decreaseHealth();
	int getX();
	int getY();
	int getHealth();

};