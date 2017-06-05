#ifndef _BALL
#define _BALL
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include "elements.h"
	#include "bar.h"

	static unsigned int DEFAULT_XPOS_BALL = 10;
	static unsigned int DEFAULT_YPOS_BALL = 10;
	static unsigned int DEFAULT_XDIR_BALL = 20;
	static unsigned int DEFAULT_YDIR_BALL = 20;


	Ball * initBall();
	void displayBall(Ball * b);
	void setBallPosition(Ball * b, int x, int y);
	int collision(Ball * b, Bar bar1, Bar bar2);
	void animateBall(Ball * b, float time);

#endif
