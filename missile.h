#pragma once
#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
using namespace std;

class MissileClass {
public:
	MissileClass(int x, int y, ALLEGRO_BITMAP* pic);
	void move();
	void draw();
	void kill();
	bool offScreen();
	bool isAlive();
	int getx();
	int gety();
	void shoot(int x, int y);
	bool collide(double x, double y);
private:
	double xPos;
	double yPos;
	double angle;
	double radius;
	bool Alive;
	ALLEGRO_BITMAP* image;

};
