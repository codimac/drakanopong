#ifndef _BRICK
#define _BRICK
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include <SDL/SDL_image.h>
	#include "utils.h"
	#include "elements.h"

	static unsigned int BRICK_HEIGHT = 30;
	static unsigned int BRICK_WIDTH = 40;
	/* ENUM */
	typedef enum TypeBrick {
		EMPTY = -1, HIDDEN,BASIC, ELIXIR, WALL, EXPAND_PLAYER_BAR
	}TypeBrick;

	/* STRUCT */
	typedef struct Brick {
		int type;
		int display;
		int durability;
		Color4f color;
		Point position;
	} Brick;

	void displayBrick(Brick brick);
	void initBrick(Brick *b);
#endif
