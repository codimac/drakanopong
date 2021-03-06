#ifndef _BAR
#define _BAR
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include "elements.h"
	#include "utils.h"

	static unsigned int MARGIN_BAR = 25;
	static unsigned int DEFAULT_WIDTH_BAR = 75;
	static unsigned int DEFAULT_SPEED_BAR = 10;

	typedef enum Direction {
		left, right
	} Direction;

	typedef struct Bar {
		Point position;
		Vector speed;
		float size;
		Color4f color;
	} Bar;

	Bar initBar();
	void moveBar(Bar *b, int direction);
	void displayBar(const Bar b);
	void setBarPosition(Bar *b, int x, int y);
	void updateSizeBar(Bar *b, float mult);
#endif
