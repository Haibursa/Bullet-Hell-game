#include "stars.h"
#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
using namespace std;

star::star() {
	xPos = rand() % 1000;
	yPos = rand() % 1000;
	r = rand() % 50;
	g = rand() % 255;
	b = rand() % 255;
	size = rand() % 10;
}

void star::draw() {
	al_draw_filled_circle(xPos, yPos, size, al_map_rgb(r, g, b));

}

void star::reposition() {
	if (yPos >= 1000) {
		r = rand() % 5;
		g = rand() % 50;
		b = rand() % 5;
		size = rand() % 5;
		xPos = rand() % 1000;
		yPos = 0;
	}
}

void star::move() {
	yPos += 10;
}
