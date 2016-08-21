/*
 * agent.cpp
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#include "bullet.h"
#include "draw.h"
#include "world.h"

Bullet::Bullet() {
	speed = -1;
}

Bullet::Bullet(int x, int y, int d, int s) {
	// TODO Auto-generated constructor stub

	speed = INITIAL_SPEED*2 + s;
	direction = d;

	position = {x, y};

}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}


void Bullet::draw() {
	Draw::bullet(position[0], position[1], direction);
}
