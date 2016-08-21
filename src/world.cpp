/*
 * World.cpp
 *
 *  Created on: 9 Dec 2015
 *      Author: Mason
 */

#include "world.h"
#include "draw.h"
#include "agent.h"
#include "ship.h"
#include "bullet.h"
#include "math.h"

#include <vector>



const int World::PLAYERS = 2;
std::vector<int> World::resolution = {10000, 10000};
int World::collisionRange = World::resolution[0] / 10;
double World::full_distance = sqrt(World::resolution[0]/100*World::resolution[0]/100 + World::resolution[1]/100*World::resolution[1]/100);

std::vector<Ship> World::ships;	// Set of all agents in the world


void World::initWorld() {

	for (int i = 0; i < PLAYERS; i++) {
		addS(new Ship(i));
	}
}

void World::worldTick() { // Go through and do everything in the world

	for (int i = 0; i < ships.size(); i++) {
		ships[i].gravity();

		ships[i].move();
		ships[i].offScreen();

		int x = ships[i].getPosition()[0]/100;
		int y = ships[i].getPosition()[1]/100;
		double distance = sqrt(x*x+y*y);
		if (distance < collisionRange/150) {
			ships[i].dead();
		}

		if (ships[i].bullet.getSpeed() != -1) {
			int a = ships[i].bullet.getSpeed();
			ships[i].bullet.move();
			ships[i].bullet.offScreen();
		}
		for (int j = i; j < ships.size(); j++) {

			if (i != j) {
				int x = (ships[i].getPosition()[0] - ships[j].getPosition()[0])/100;
				int y = (ships[i].getPosition()[1] - ships[j].getPosition()[1])/100;
				double distance = sqrt(x*x+y*y);
				if (distance < collisionRange/150) {
					ships[j].dead();
					ships[i].dead();
				}
			}


			if (ships[i].bullet.getSpeed() != -1) {
				int x = (ships[i].bullet.getPosition()[0] - ships[j].getPosition()[0])/100;
				int y = (ships[i].bullet.getPosition()[1] - ships[j].getPosition()[1])/100;
				int s = x*x+y*y;
				double distance = sqrt(s);
				if (distance < collisionRange/150) {
					ships[j].dead();
					ships[i].hit();
				}
			}
		}
	}


}

void World::addS(Ship* a) {			// I think with the hash thing I could just collect the agent I need with the hash thing
	ships.push_back(*a);
}


std::vector<int> World::twoForces(int direction_one, int speed_one, int direction_two, double speed_two) {
								// determine the new heading a speed, based upon the two acting forces, probably not proper physics

	if (speed_one <= 0) {
		return {direction_two, speed_two};
	} else if (speed_two <= 0) {
		return {direction_one, speed_one+speed_two};
	} else if (direction_one == direction_two) {
		return {direction_one, speed_two+speed_one};
	}

	bool neg = false;
	int dir = (direction_one+180) - (direction_two+180);
	if (dir < 0) {
		neg = !neg;
		dir = -dir;
	}

	if (dir >= 180) {
		dir = 360-dir;
		neg = !neg;
	}

	// should also depend on the speed
	int r = dir/30;
	double speed_ratio = speed_two / speed_one;


	// this was determining how much force two should effect force one based upon the angle rather than the speed
	if (r == 0) {

	} else {
//		dir = dir/r * speed_ratio;
//		speed_one = speed_one/r;
	}

	speed_two = cos(dir*Draw::DEG2RAD)*speed_two;

	if (r == 6) {	// opposite direction so just slow down

	} else {
		dir = dir/(speed_ratio + 1);
	}

	// here I think is making it weird
/*	if (r >= 4) {
		speed_two = -speed_two;
	} else if (r >= 2) {
		speed_two = 0;
//		direction_two = direction_one;
	}
*/

	if (neg) {
		dir = -dir;
	}
	int speed = speed_one + speed_two;
	if (speed < 0) {
		dir = 0;
		speed = -speed;
	}
	int direction = direction_two+dir;


	return {direction, speed};
}


