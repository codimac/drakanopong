#ifndef _LEVEL
#define _LEVEL
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include <SDL/SDL_image.h>
	#include "utils.h"
	#include "elements.h"

	#define MAX_BRICK 100
	#define MAX_ROW 6
	#define MAX_COLUMN 10

	/* ENUM */
	typedef enum TypeBrick {
		basics, explosion,
	}TypeBrick;

	/* STRUCT */
	typedef struct Brick {
		int type;
		int display;
		int durability;
		Color4f color;
	} Brick;

	typedef struct Level {
		char  * lvl;
		char filename [15];
		int nbBrickX;
		int nbBrickY;
		int nbBrickTotal;
		int hit; /* number of hit required to destroy */
		Brick brick[MAX_BRICK];
	} Level;

	/**
	 * FUNCTIONS
	 **/

	Level initLevel();
	void setGameLevel(Level * level, char * gameLevel);
	void loadLevel(Level level);
	/*Brick brick[MAX_BRICK];*/

#endif
