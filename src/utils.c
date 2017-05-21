#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "utils.h"

/**
 * int axis : 1 for width, -1 for height
 * int mark : WINDOW_WIDTH / WINDOW_HEIGHT / GAME_WIDTH / GAME_HEIGHT ...
 * return float value between -1 and 1
**/
float convertPixelToMark(int pixel, int mark, int axis){
	return axis*(-1+2* (float) pixel/mark);
}
/**
 * int axis : 1 for width, -1 for height
 * int mark : WINDOW_WIDTH / WINDOW_HEIGHT / GAME_WIDTH / GAME_HEIGHT ...
 * return float value between -1 and 1
 * same as convertPixelToMark BUT center the value on the origin.
**/
float centeredPixelToMark(int pixel, int mark, int axis) {
	pixel = (mark - pixel) /2;
	return axis*(-1+2* (float) pixel/mark);
}

/*
 * Draw a rectangle.
 */
void rectangle(float width, float height){
	glBegin(GL_POLYGON);
		glVertex2f(-width,-height);
		glVertex2f(width,-height);
		glVertex2f(width,height);
		glVertex2f(-width,height);
	glEnd();
}
