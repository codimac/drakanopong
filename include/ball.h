#ifndef _BALL
#define _BALL
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include "elements.h"


	Ball * initBall();
	/*void moveBar(Bar b, int direction);*/
	void displayBall(const Ball * b);
	void setBallPosition(Ball * b, int x, int y);
	void animateBall(Ball * b, float time);

#endif
