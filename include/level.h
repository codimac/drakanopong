#ifndef _LEVEL
#define _LEVEL
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include "utils.h"
	#include "elements.h"

	static unsigned int MAX_BRICK = 100;

	typedef struct Level {
		char  * lvl;
		char filename [15];
		int nbBrickX;
		int nbBrickY;
		int nbBrickTotal;
	} Level;

	Level initLevel();
	void setGameLevel(Level * level, char * gameLevel);
	void loadLevel(Level level);
	/*Brick brick[MAX_BRICK];*/

#endif
