#ifndef _PLAYER
#define _PLAYER
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include "elements.h"
	#include "bar.h"

	static unsigned int DEFAULT_HEARTS = 5;

	/* PLAYERS */
	typedef struct Player {
		char name;
		int lives;
		int score;
		Bar bar;
	} Player;

	Player initPlayer(char name[]);
	void updateLives(Player *p, int offset);
#endif
