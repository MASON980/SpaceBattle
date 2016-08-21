/*
 * orb.cpp
 *
 *  Created on: 17 Feb 2016
 *      Author: Mason
 */

#include "agent.h"
#include "ship.h"
#include "draw.h"
#include "world.h"
#include "bullet.h"
#include <stdlib.h>
#include <math.h>

const int Ship::MAX_SPEED = 25000;

Bullet bullet = *(new Bullet());
int facing;
int deaths;
std::vector<int> spawn (2);

Ship::Ship(int p) {
	// TODO Auto-generated constructor stub

	speed = INITIAL_SPEED;

	int d = 360 / World::PLAYERS;
	direction = p*d;

	double dir =  direction * Draw::DEG2RAD;
	int rx = World::getResolution()[0]/2;
	int ry = World::getResolution()[1]/2;
	int x = cos(dir) * rx;
	int y = sin(dir) * ry;
	facing = direction;
	position = {x, y};

	deaths = 0;
	spawn = position;

}

Ship::~Ship() {
	// TODO Auto-generated destructor stub
}



void Ship::turn(int d) {
	this->facing = this->facing + d;

	clean();
}


void Ship::cellerate(int d) {		// accelerate or decellerate depending on d

	std::vector<int> v = World::twoForces(direction, speed, facing, d);
	direction = v[0];
	speed = v[1];
//	this->speed = this->speed + d;
	clean();

}

void Ship::gravity() {			// apply the gravity of the sun to the ship

	int x = position[0]/100;
	int y = position[1]/100;

	double distance_from_center = sqrt(x*x+y*y);

	double angle_from_center = atan2(-position[1], -position[0]);		// it likes negatives
	int a = angle_from_center/Draw::DEG2RAD;
	double strength_of_pull = World::getFullDistance() / distance_from_center * 20;

	std::vector<int> v = World::twoForces(direction, speed, a, strength_of_pull);
	direction = v[0];
	speed = v[1];

	clean();

}

void Ship::clean() {				// if the ship is ever going faster than the max, or turning to far in one direction this will carry it over

	if (this->speed >= MAX_SPEED) {			// speed too high
		this->speed = MAX_SPEED;
	} else if (speed <= 0) {				// or too low
		direction = facing;
		speed = 0;
	}
	if (this->facing >= 180) {				// turning too far, carry
		this->facing = this->facing - 360;
	} else if (facing < -180) {
		facing = facing + 360;
	}
	if (this->direction >= 180) {				// turning too far, carry
		this->direction = this->direction - 360;
	} else if (direction < -180) {				// turning too far, carry
		direction = direction + 360;
	}
}

void Ship::shoot() {	// shoot a bullet slightly ahead of the ship so they don't hit
	double dir =  this->facing * Draw::DEG2RAD;
	double x = cos(dir) * (2+World::getCollisionRange()/1);
	double y = sin(dir) * (2+World::getCollisionRange()/1);
	int px = this->position[0] + round(x);
	int py = this->position[1] + round(y);
	int c = cos((facing-direction)*Draw::DEG2RAD)*speed;
	Bullet* b = new Bullet(px, py, facing, c);
	bullet = *b;
}

void Ship::jump() {			// teleport randomly

	int dx = World::getResolution()[0]/100;
	int dy = World::getResolution()[1]/100;
	int x = rand() % (dx*2) - dx;
	int y = rand() % (dy*2) - dy;
	position = {x*100, y*100};
}

void Ship::draw() {
	Draw::ship(position[0], position[1], facing);
	Draw::score(spawn[0], spawn[1], deaths);
}

void Ship::hit() {	// when the ship is hit by a bullet
	bullet = *(new Bullet());
}

void Ship::dead() {	// when the ship is hit by a bullet
	jump();
	speed = 0;
	deaths++;
}
