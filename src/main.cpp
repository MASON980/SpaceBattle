/*
 * main.cpp
 *
 *  Created on: 8 Dec 2015
 *      Author: Mason
 */

#include "draw.h"
#include "main.h"
#include <ctime>
#include <stdlib.h>


int main(int argc, char* argv[])
{
	srand(time(0));
	Draw::initialiseDraw();
    return 0;
}

