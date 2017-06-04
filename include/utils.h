#ifndef _UTILS
#define _UTILS
	#include <stdlib.h>
	#include <stdio.h>
	#include "elements.h"
#define M_PI 3.14159265358979323846

	typedef enum Axis{
		axisX = 1, axisY = -1
	}Axis;


float convertPixelToMark(int pixel, int mark, int axis);
float centeredPixelToMark(int pixel, int mark, int axis);
float convertCoordToMark(float pixel, int mark);
void rectangle(float width, float height);
void circle(float radius, Color4f color);

#endif
