/*
 * world.h
 *
 *  Created on: 9 Dec 2015
 *      Author: Mason
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "agent.h"
#include "bullet.h"
#include "ship.h"

#include <array>
#include <vector>

class World {
private:

	static int collisionRange;
	static std::vector<int> resolution;
	static double full_distance;

public:
	static std::vector<Ship> ships;	// Set of all agents in the world
	static std::vector<Bullet> bullets;

	const static int PLAYERS;

	static void initWorld();
	static void worldTick(); // Go through and do everything in the world, agent logic then draw

	static std::vector<Ship> getS() { return ships;}
	static void addS(Ship*);

	static std::vector<int> getResolution() { return World::resolution;}
	static int getCollisionRange() { return collisionRange;}
	static double getFullDistance() {return full_distance;};

	static std::vector<int> twoForces(int, int, int, double);


};


#endif /* WORLD_H_ */
