#ifndef _LEVEL
#define _LEVEL
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include "utils.h"
	#include "elements.h"
	#include "game.h"

	static unsigned int MAX_BRICK = 100;

	typedef struct Level {
		int lvl;
		char filename [15];
	} Level;
	/*Brick brick[MAX_BRICK];*/
	/*void loadLevel(Game game);*/
#endif
