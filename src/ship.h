/*
 * orb.h
 *
 *  Created on: 17 Feb 2016
 *      Author: Mason
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "agent.h"
#include "bullet.h"

class Ship: public Agent {
private:
	static const int MAX_SPEED;

	int facing;
	int deaths;
	std::vector<int> spawn;
public:
	Bullet bullet;


	Ship(int);
	virtual ~Ship();

	Bullet getBullet() {return bullet;};
	int getFacing() {return facing;};
	int getDeaths() {return deaths;};
	std::vector<int> getSpawn() {return spawn;};

	void gravity();
	void turn(int);
	void cellerate(int);
	void shoot();
	void jump();
	void hit();
	void dead();
	void clean();

	void draw();

};

#endif /* SHIP_H_ */
