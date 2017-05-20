#ifndef _BAR
#define _BAR
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include "elements.h"
	typedef enum Direction {
		left, right, stop
	} Direction;
	Bar initBar();
	void moveBar(Bar b, int direction);
	void displayBar(const Bar b);
	void setBarPosition(Bar *b, int x, int y);

#endif
