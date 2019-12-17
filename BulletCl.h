#pragma once
#include<iostream>
using namespace std;

class BulletClass {
public:
	BulletClass(int x, int y);
	void move();
	void draw();
	void kill();
	bool offScreen();
	bool isAlive();
	int getx();
	int gety();
	void shoot(int x, int y);
	bool collide(double x, double y);
	BulletClass();
private:
	double angle;
	double radius;
	double xPos;
	double yPos;
	bool Alive;
};