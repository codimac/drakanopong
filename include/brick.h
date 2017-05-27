#ifndef _BRICK
#define _BRICK
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <GL/gl.h>
	#include <SDL/SDL_image.h>
	#include "utils.h"
	#include "elements.h"
	#include "texture.h"

	#define NB_TYPE_BRICK 6

	static unsigned int BRICK_HEIGHT = 20;
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
		Point position;
		GLuint textureId;
	} Brick;

	void displayBrick(Brick brick);
	void initBrick(Brick *b, float x, float y);
#endif
