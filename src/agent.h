/*
 * Agent.h
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#ifndef AGENT_H_
#define AGENT_H_

// Agent is for each circle or whatever, and its movement and logic behind that movement

#include <functional>
#include <vector>
#include <map>
#include <iterator>


using namespace std;



class Agent {

protected:
	int const static INITIAL_SPEED; // All agents can start at the same speed, thats not really important
	int speed;			// Speed of the agent
	int direction;		// Direction of the agent, using 360 degrees
	std::vector<int> position;		// Position of the agent


public:

	Agent();
	virtual ~Agent();
	int getSpeed() const { return speed;}
	int getDirection() const { return direction;}


	// this sometimes doesn't work with iterators
	std::vector<int> getPosition() const {
		return position;
	}
	void move();
	void offScreen();

	virtual void draw() {return;};

};

#endif /* AGENT_H_ */
