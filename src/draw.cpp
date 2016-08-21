/*
 * Draw.cpp
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#include "draw.h"
#include "agent.h"
#include "world.h"
#include <windows.h>  // For MS Windows
#include <math.h>

#define FREEGLUT_STATIC
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h


#include <stdio.h>		// sprintf

// Glut init
char *myargv[1];
char v = ' ';
int myargc = 1;

const float Draw::DEG2RAD = 3.14159 / 180;
const int Draw::STARTING_HEIGHT = 720;
const int Draw::STARTING_WIDTH = 1080;

long Draw::prev = 0;


int Draw::frame_height = Draw::STARTING_HEIGHT;
// maybe left top or something
float Draw::height = 1;
float Draw::width = 1;
float Draw::ratio  = Draw::width / Draw::height;
bool Draw::paused = false;

void Draw::circle(int x, int y, int id) {
	glColor3d(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);         // Each set of 4 vertices form a something

	double  fx = x * Draw::width / World::getResolution()[0];
	double fy = y * Draw::height / World::getResolution()[1];
	for (int i = 0; i <= 36; i++) {
		float degInRad = i * Draw::DEG2RAD * 10;		// 10 * 36(used for how many loops) is where the 360 degrees come from
		glVertex2d(fx + cos(degInRad) * World::getCollisionRange()/World::getResolution()[0] * Draw::ratio,
				fy + sin(degInRad) * World::getCollisionRange()/World::getResolution()[1]);
	}
	glEnd();
}

void Draw::ship(int x, int y, int d) {
	glBegin(GL_TRIANGLE_FAN);         // Each set of 4 vertices form a something

	// change the colour depending on the status of the thing (moving or not)	-	maybe

	double  fx = x * Draw::width / World::getResolution()[0];
	double fy = y * Draw::height / World::getResolution()[1];
	//float fy = (1 - y * height) / 100;
	float degInRad = Draw::DEG2RAD * d;		// 10 * 36(used for how many loops) is where the 360 degrees come from
	glVertex2d(fx + cos(degInRad) * 0.06 * Draw::ratio,
				fy + sin(degInRad) * 0.06);

	degInRad = Draw::DEG2RAD * (d+90);		// 10 * 36(used for how many loops) is where the 360 degrees come from
	glVertex2d(fx + cos(degInRad) * 0.02 * Draw::ratio,
				fy + sin(degInRad) * 0.02);

	degInRad = Draw::DEG2RAD * (d-90);		// 10 * 36(used for how many loops) is where the 360 degrees come from
	glVertex2d(fx + cos(degInRad) * 0.02 * Draw::ratio,
				fy + sin(degInRad) * 0.02);


	glEnd();

}

void Draw::bullet(int x, int y, int d) {
	glColor3f(1.0f, 0.0f, 0.0f); // Red

	glLineWidth(2.5);
	glBegin(GL_LINES);

	// change the colour depending on the status of the thing (moving or not)	-	maybe

	double  fx = x * Draw::width / World::getResolution()[0];
	double fy = y * Draw::height / World::getResolution()[1];

	glVertex2d(fx, fy);

	float degInRad = Draw::DEG2RAD * d;		// 10 * 36(used for how many loops) is where the 360 degrees come from
	glVertex2d(fx + cos(degInRad) * 0.02 * Draw::ratio,
				fy + sin(degInRad) * 0.02);


	glEnd();
}

void Draw::score(int x, int y, int d) {			// draw the score, the score just resets after every 10 at the moment

	double  fx = x * Draw::width / World::getResolution()[0];
	double fy = y * Draw::height / World::getResolution()[1];

	glRasterPos2d(fx, fy); // line
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (d%10) + 48);
	glEnd();
}


void Draw::display() {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to white and opaque


	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	circle(0, 0, 0);
	std::vector<Ship> s = World::getS();

	for (int i = 0; i < s.size(); i++) {
		colouring(i);
		s[i].draw();
		if (s[i].getBullet().getSpeed() != -1) {
			s[i].getBullet().draw();
		}

	}

	glFlush();  // Render now
}

void Draw::time(int i) {

	if (paused) {
//		Draw::stringWithInt("Paused", NULL);
	} else {
		World::worldTick();
	}

	glutPostRedisplay();
	glutTimerFunc(20, time, 0);

}

void Draw::colouring(int c) {

	if (c == 0) {
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 1) {
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 2) {
		glColor4f(1.0f, 0.0f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 3) {
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 4) {
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 5) {
		glColor4f(0.3f, 0.6f, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 6) {
		glColor4f(0.7f, 0.7, 1.0f, 1.0f); // Set background color to white and opaque
	} else if (c == 7) {
		glColor4f(1.0f, 0.5f, 0.5f, 1.0f); // Set background color to white and opaque
	} else if (c == 8) {
		glColor4f(0.5f, 1.0f, 0.5f, 1.0f); // Set background color to white and opaque
	}
}


void Draw::reshape(int new_width, int new_height) {
	Draw::height = (float) new_height / Draw::STARTING_HEIGHT;
	Draw::width =  (float) new_width / Draw::STARTING_WIDTH;
	Draw::ratio = Draw::width / Draw::height;
	Draw::frame_height = new_height;

}

void Draw::initialiseDraw() {
	// TODO Auto-generated constructor stub

	World::initWorld();

	myargv[0] = &v;
	glutInit(&myargc, myargv);
	glutInitWindowSize(Draw::STARTING_WIDTH, Draw::STARTING_HEIGHT); // Set the window's initial width & height
	glutInitWindowPosition(50, 100); // Position the window's initial top-left corner
	glutCreateWindow(
			"SpaceBattle?"); // Create a window with the given title
	glutDisplayFunc(Draw::display);
//	glutIdleFunc(Draw::display); // Register display callback handler for window re-paint
	glutReshapeFunc(Draw::reshape);
	glutKeyboardFunc(Draw::key);
	//glutMouseFunc(World::mouse);
	//glutPassiveMotionFunc(World::passiveMouse);
	glutSpecialFunc(Draw::specialKey);
	Draw::time(0);

	glutMainLoop();           // Enter the infinitely event-processing loop
}

std::vector< int > Draw::pixelToGlut(int px, int py) {				// transform a coord in pixels to a coord in glut units
	// could just save the actual height and width
	double current_height = Draw::height * Draw::STARTING_HEIGHT;
	double current_width =  Draw::width * Draw::STARTING_WIDTH;

//	double dx = ((px / current_width) * 2 - 1) * World::getResolution();
//	double dy = ((1 - (py / current_height)) * 2 - 1) * World::getResolution();
	// 1, 1 is now bottom right
		// has a problem with some negatives, I think primarily negative y

	double dx = ((px / current_width) * 2) * World::getResolution()[0];
	double dy = ((1 - (py / current_height)) * 2) * World::getResolution()[1];

	int x = dx;
	int y = dy;

	return std::vector<int> {x, y};
}





void Draw::mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		return;
	}

	glutPostRedisplay();

}


void Draw::key(unsigned char k, int x, int y){
	int a = 5000;
	int t = 10;

	if (k == ' ') {
		paused = !paused;
	}

	// controls for all the players
	//p1
	int p = 0;
	if (k == 'w') {
		World::ships[p].cellerate(a);
	}
	if (k == 'a') {
		World::ships[p].turn(t);
	}
	if (k == 's') {
		World::ships[p].cellerate(-a);
	}
	if (k == 'd') {
		World::ships[p].turn(-t);
	}
	if (k == 'q') {
		World::ships[p].jump();
	}
	if (k == 'e') {
		World::ships[p].shoot();
	}


	// p2
	p = 1;
	if (k == 'i') {
		World::ships[p].cellerate(a);
	}
	if (k == 'j') {
		World::ships[p].turn(t);
	}
	if (k == 'k') {
		World::ships[p].cellerate(-a);
	}
	if (k == 'l') {
		World::ships[p].turn(-t);
	}
	if (k == 'u') {
		World::ships[p].jump();
	}
	if (k == 'o') {
		World::ships[p].shoot();
	}
/*
	//p1
	int p = 0;
	if (k == '2') {
		World::ships[p].cellerate(a);
	}
	if (k == 'q') {
		World::ships[p].turn(t);
	}
	if (k == 'w') {
		World::ships[p].cellerate(-a);
	}
	if (k == 'e') {
		World::ships[p].turn(-t);
	}
	if (k == '3') {
		World::ships[p].jump();
	}
	if (k == '1') {
		World::ships[p].shoot();
	}


	// p2
	p = 1;
	if (k == '5') {
		World::ships[p].cellerate(a);
	}
	if (k == 'r') {
		World::ships[p].turn(t);
	}
	if (k == 't') {
		World::ships[p].cellerate(-a);
	}
	if (k == 'y') {
		World::ships[p].turn(-t);
	}
	if (k == '6') {
		World::ships[p].jump();
	}
	if (k == '4') {
		World::ships[p].shoot();
	}

	//p3
	p = 2;
	if (k == '8') {
		World::ships[p].cellerate(a);
	}
	if (k == 'u') {
		World::ships[p].turn(t);
	}
	if (k == 'i') {
		World::ships[p].cellerate(-a);
	}
	if (k == 'o') {
		World::ships[p].turn(-t);
	}
	if (k == '9') {
		World::ships[p].jump();
	}
	if (k == '7') {
		World::ships[p].shoot();
	}


	// p4
	p = 3;
	if (k == '-') {
		World::ships[p].cellerate(a);
	}
	if (k == 'p') {
		World::ships[p].turn(t);
	}
	if (k == '[') {
		World::ships[p].cellerate(-a);
	}
	if (k == ']') {
		World::ships[p].turn(-t);
	}
	if (k == '=') {
		World::ships[p].jump();
	}
	if (k == '0') {
		World::ships[p].shoot();
	}

	//p5
	p = 4;
	if (k == 's') {
		World::ships[p].cellerate(a);
	}
	if (k == 'z') {
		World::ships[p].turn(t);
	}
	if (k == 'x') {
		World::ships[p].cellerate(-a);
	}
	if (k == 'c') {
		World::ships[p].turn(-t);
	}
	if (k == 'd') {
		World::ships[p].jump();
	}
	if (k == 'a') {
		World::ships[p].shoot();
	}


	// p6
	p = 5;
	if (k == 'g') {
		World::ships[p].cellerate(a);
	}
	if (k == 'v') {
		World::ships[p].turn(t);
	}
	if (k == 'b') {
		World::ships[p].cellerate(-a);
	}
	if (k == 'n') {
		World::ships[p].turn(-t);
	}
	if (k == 'h') {
		World::ships[p].jump();
	}
	if (k == 'f') {
		World::ships[p].shoot();
	}

	//p7
	p = 6;
	if (k == 'k') {
		World::ships[p].cellerate(a);
	}
	if (k == 'm') {
		World::ships[p].turn(t);
	}
	if (k == ',') {
		World::ships[p].cellerate(-a);
	}
	if (k == '.') {
		World::ships[p].turn(-t);
	}
	if (k == 'l') {
		World::ships[p].jump();
	}
	if (k == 'j') {
		World::ships[p].shoot();
	}


	// p8
	p = 7;

	if (k == ';') {
		World::ships[p].jump();
	}
	if (k == '/') {
		World::ships[p].shoot();
	}

*/

}

void Draw::passiveMouse(int x, int y) {

}



void Draw::specialKey(int key, int x, int y) {
	int p = 7;
	int a = 5000;
	int t = 10;

	if (key == GLUT_KEY_UP) {
		World::ships[p].cellerate(a);
	}
	if (key == GLUT_KEY_DOWN) {
		World::ships[p].cellerate(-a);
	}

	if (key == GLUT_KEY_LEFT) {
		World::ships[p].turn(t);
	}
	if (key == GLUT_KEY_RIGHT) {
		World::ships[p].turn(-t);
	}

//	glutPostRedisplay();
}
