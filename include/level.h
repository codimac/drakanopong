#ifndef _LEVEL
#define _LEVEL
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include <SDL/SDL_image.h>
	#include "utils.h"
	#include "elements.h"
	#include "brick.h"

	#define MAX_BRICK 100
	#define MAX_ROW 6
	#define MAX_COLUMN 10

	/* STRUCT */


	typedef struct Level {
		char  * lvl;
		char filename [15];
		int nbBrickX;
		int nbBrickY;
		int nbBrickTotal;
		Brick brick[MAX_BRICK];
	} Level;

	/**
	 * FUNCTIONS
	 **/

	Level initLevel();
	void setGameLevel(Level * level, char * gameLevel);
	void loadLevel(Level * level);
	void displayConsole(Level level);
	void displayLevel(Level level);
#endif
