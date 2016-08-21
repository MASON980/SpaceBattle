/*
 * Draw.h
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <string>
#include "agent.h"
#include <vector>

// Draw is for drawing the GUI/Graphics to make stuff easier to follow for humans

class Draw {

private:
	//static char *myargv;
	//static char v;
	//static int myargc;

	static const int STARTING_HEIGHT;
	static const int STARTING_WIDTH;
	static int frame_height;
	static float height;
	static float width;
	static int frames;

	static long prev;
	static bool paused;


public:

	static const float DEG2RAD;
	static float ratio;	// it was complaining about this being private

	static void initialiseDraw();
	static void display();
	static void time(int);
	static void reshape(int, int);

	static void circle(int, int, int);
	static void ship(int, int, int);
	static void bullet(int, int, int);
	static void score(int, int, int);

	static void colouring(int);
	static std::vector<int> pixelToGlut(int, int);

	static void mouse(int, int, int , int);
	static void key(unsigned char, int , int);
	static void passiveMouse(int, int);
	static void specialKey(int, int, int);

};

#endif /* DRAW_H_ */
