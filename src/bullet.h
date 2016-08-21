/*
 * Agent.h
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "agent.h"

class Bullet: public Agent  {

public:
	Bullet();
	Bullet(int, int, int, int);
	virtual ~Bullet();

	void draw();
	void dead();
};

#endif /* AGENT_H_ */
