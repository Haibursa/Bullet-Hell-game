///////////////////////////////////////////
#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<iostream>
#include"stars.h"
#include<vector>
#include"mothership.h"
#include "missile.h"
#include"BulletCl.h"
using namespace std;
//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 1000;
const int SCREEN_H = 1000;
//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};
enum DIRECTIONS {
	UP, DOWN, LEFT, RIGHT
};

int i = 0;
int minBullets = 60;
int main()
{
	cout << "flag" << endl;
	vector<star*> starfield;
	vector<star*>::iterator iter3;
	for (int i = 0; i <= 100; i++) {
		star* newStar = new star();
		starfield.push_back(newStar);
	}
	//set up allegro
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();

	//set up game screen, event queue, and timer
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	al_start_timer(timer);
	ALLEGRO_BITMAP* shipPic = al_load_bitmap("ship.png");
	ALLEGRO_BITMAP* missilePic = al_load_bitmap("missile.png");
	ALLEGRO_BITMAP* pic = al_load_bitmap("mothership.png");
	ALLEGRO_BITMAP* dinopic = al_load_bitmap("image1.png");
	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
	if (pic == NULL)cout << "ruh roh" << endl;

	ALLEGRO_BITMAP* explosion = al_load_bitmap("bigboom.png");
	//start dark for a second
	//for (float i = 0; i < 1; i += .0005) {
	//	al_clear_to_color(al_map_rgb(0, 0, 0));
	//}
	////fade in
	//for (float i = 0; i < 1; i += .0008) {
	//	al_clear_to_color(al_map_rgb(0, 0, 0));
	//	al_draw_tinted_bitmap(dinopic, al_map_rgba_f(1, 1, 1, i), 50, 50, 0);
	//	al_flip_display();
	//}
	////stay solid for a second
	//for (float i = 0; i < 1; i += .001) {
	//	al_clear_to_color(al_map_rgb(0, 0, 0));
	//	al_draw_tinted_bitmap(dinopic, al_map_rgba_f(1, 1, 1, 1), 50, 50, 0);
	//	al_flip_display();
	//}
	////fade out
	//for (float i = 1; i > 0; i -= .0005) {
	//	al_clear_to_color(al_map_rgb(0, 0, 0));
	//	al_draw_tinted_bitmap(dinopic, al_map_rgba_f(i, 1, 1, i), 50, 50, 0);
	//	al_flip_display();
	//}

	//al_rest(5);

	//al_destroy_bitmap(dinopic);

	//position of player
	double xPos = 400;
	double yPos = 700;

	//game variables
	bool key[5] = { false, false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop
	int ticker = 0;
	int cellNum = 0;
	int curFrame = 0;
	int dir = 0;
	int justShot = 0;
	int AlienHit = 0;
	int hitX = 0;
	int hitY = 0;


	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//vector to hold missiles
	vector<MissileClass*> missiles;
	vector<MissileClass*>::iterator iter2;
	for (int i = 0; i < 5; i++) {
		MissileClass* newMissile = new MissileClass(0, 3, 0);
		missiles.push_back(newMissile);
	}
	AlienShip A1(60, 60, pic);

	//vector to hold bullets
	vector<BulletClass*> bullets;
	vector<BulletClass*>::iterator iter5;
	for (int j = 0; i < 5; i++) {
		BulletClass* newBullet = new BulletClass(10.9, 7);
		bullets.push_back(newBullet);
	}
	int counter=0;
	while (!doexit)//game loop!
	{
		//cout << "flag1" << endl;
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			justShot++;
			//cout << "flag2" << endl;

			counter++;//varible to slow down object creation
			minBullets -= .001;
			if (counter > minBullets) {
				//create new bullets, push into vector

				BulletClass *newbullet = new BulletClass(A1.getX(), A1.getY());
				bullets.push_back(newbullet);
				newbullet->shoot(A1.getX() + 40, A1.getY() + 40);
				newbullet->shoot(A1.getX() + 40, A1.getY() + 40);
				//cout << "pushing.";
				counter = 0;
			}
			//cull the bullets that are off the screen
			for (iter5 = bullets.begin(); iter5 != bullets.end(); iter5++) {
				if ((*iter5)->offScreen()) {
					(*iter5)->~BulletClass();//call the DESTRUCTOR(destroys the object, releases memory)
					iter5 = bullets.erase(iter5);//take it out of the vector,too
					cout << "destroying stuff." << endl;
				}
			}

			for (iter5 = bullets.begin(); iter5 != bullets.end(); iter5++) {
				//(*iter5)->shoot(A1.getX() + 40, A1.getY() + 40);
				(*iter5)->move();
				//cout << "hello";
			}


			//check missile colliosn w/Mothership
		//	cout << "collison with mothership" << endl;
			for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
				if ( (*iter2)->isAlive()&&(*iter2)->collide(A1.getX() + 40, A1.getY() + 40    )) {
					A1.decreaseHealth();
						//cout << "mothership hit!" << endl;
						AlienHit = 30;
						hitX = (*iter2)->getx();
						hitY = (*iter2)->gety();
				}

			}
			A1.move();

				//move the stars
		//	cout << "STARS" << endl;
				for (iter3 = starfield.begin(); iter3 != starfield.end(); iter3++) {
					(*iter3)->reposition();
					(*iter3)->move();
				}

			//move the missiles
			for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
				if ((*iter2)->isAlive())
					(*iter2)->move();
			}
			//cull (kill) the missiles
			for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
				if ((*iter2)->offScreen())
					(*iter2)->kill();
				//cout << "missiles" << endl;
			}
			

			//this is to slow donw your animation
		//(otherwise it moves at the speed of your game loop)
			ticker++;
			if (ticker > 10)
				ticker = 0;
			if (ticker == 0)
				cellNum++;
			//move the player ship animation forward, loop bakc after 4 cells
			if (dir == UP || dir == DOWN) {

				if (cellNum > 4)
					cellNum = 0;
			}
			if (dir == LEFT || dir == RIGHT) {
				if (cellNum < 5)
					cellNum = 5;
				if (cellNum > 9)
					cellNum = 5;
			}
			/*if (ticker == 0)
				cellNum++;
			if (cellNum > 4)
			cellNum = 0;
*/
//move player 4 pixels in a direction when key is pressed
			if (key[KEY_UP]) {
				yPos -= 4.0;
			}

			if (key[KEY_DOWN]) {
				yPos += 4.0;
			}

			if (key[KEY_LEFT]) {
				xPos -= 4.0;
			}

			if (key[KEY_RIGHT]) {
				xPos += 4.0;
			}
			if (key[KEY_SPACE]) {
				for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
					if (((*iter2)->isAlive()) == false && justShot > 10) {
						(*iter2)->shoot(xPos, yPos);
						justShot = 0;
						cout << "pew pew";
					}
				}
			}

			redraw = true;
		}

		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		//render section//////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			//cout << "render section" << endl;
			al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing (without this things smear) 

			//draw ship
			if (dir == LEFT)
				al_draw_bitmap_region(shipPic, cellNum * 32, 0, 32, 32, xPos, yPos, ALLEGRO_FLIP_HORIZONTAL);
			else
				al_draw_bitmap_region(shipPic, cellNum * 32, 0, 32, 32, xPos, yPos, NULL);
			//cout << "render section2" << endl;
			//draw missiles
			for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
				(*iter2)->draw();
				//cout << "drawing missiles" << endl;
			}
			//draw explosions
			if (AlienHit > 0) {
				al_draw_bitmap_region(explosion, curFrame * 100, 0, 100, 90, hitX - 40, hitY, 0);
				AlienHit--;
				cout << hitX << endl;
				cout << hitY << endl;
			}
			//cout << "render section3" << endl;
			//draw stars
			for (iter3 = starfield.begin(); iter3 != starfield.end(); iter3++) {
				(*iter3)->draw();
			}
			for (iter5 = bullets.begin(); iter5 != bullets.end(); iter5++) {
				(*iter5)->draw();
				//cout << "drawing BOOLETS" << endl;
			}
			//draw mothership
			A1.draw();
			

			//cout << "render section4" << endl;
			al_flip_display(); //flip everything from memory to gamescreen
		}//end render


	}//end game loop
	
	//clean up memoryggsdcooldwascd d
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
