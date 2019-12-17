#pragma once
#include<iostream>
using namespace std;


class star {
private:
	int xPos;
	int yPos;
	int size;
	int r;
	int g;
	int b;
public:
	star();
	void draw();
	void move();
	void reposition();
};