/*
 * agent.cpp
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#include "agent.h"
#include "world.h"
#include "draw.h"
#include <cstdlib>
#include <map>
#include <functional>
#include <math.h>

// Position and goal position will be randomly generated then the agent will determine how to get there (which direction to go)
// Just 2D at the moment

// Check all the other agents calculating whether based upon their position, direction and speed whether they will hit
// Skip over ones that definitely won't (position with direction don't intersect with the path being taken)
// Maybe try and estimate the size of the turn needed
// Maybe only check ones within a certain range



//int const Agent::INITIAL_SPEED = World::getResolution() / 5000; // All agents can start at the same speed, thats not really important
int const Agent::INITIAL_SPEED = 2000;

int speed;			// Speed of the agent
int direction;		// Direction of the agent, using 360 degrees
std::vector<int> position(2);		// Position of the agent


Agent::Agent() {
}

Agent::~Agent() {

}

void Agent::move() {	// Move the agent according to the direction and speed
	if (this->speed < 0) {
		return;
	}
	double dir =  this->direction * Draw::DEG2RAD;
	double x = cos(dir) * this->speed/50;
	double y = sin(dir) * this->speed/50;
	this->position[0] = this->position[0] + round(x);
	this->position[1] = this->position[1] + round(y);



}

void Agent::offScreen() {		// the agent has fallen off the screen, so put them back on the other side
	if (this->speed <= 0) {
		return;
	}

	if (position[0] < -World::getResolution()[0]) {
		position[0] = World::getResolution()[0];
		position[1] = -position[1];

	} else if (position[0] > World::getResolution()[0]) {
		position[0] = -World::getResolution()[0];
		position[1] = -position[1];

	} else if (position[1] < -World::getResolution()[1]) {
		position[1] = World::getResolution()[1];
		position[0] = -position[0];

	} else if (position[1] > World::getResolution()[1]) {
		position[1] = -World::getResolution()[1];
		position[0] = -position[0];

	}
}


