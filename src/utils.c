#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "utils.h"

#define M_PI 3.14159265358979323846264338327


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


float convertCoordToMark(float coord, int mark){
	return ((-1+2*coord)/(float)mark);
}


void rectangle(float width, float height){
	glBegin(GL_POLYGON);
		glVertex2f(-width,-height);
		glVertex2f(width,-height);
		glVertex2f(width,height);
		glVertex2f(-width,height);
	glEnd();
}


void circle(float radius){
	float angle;
  /** Dessine un cercle (plein ou non) de rayon 1 et centré en (0, 0). **/
	glBegin(GL_POLYGON);
		/*glColor3ub(0,0,255);*/
		for(angle = 0 ; angle < 2*M_PI; angle+= M_PI/16){
			glVertex2f(radius*cos(angle), radius*sin(angle));
		}
	glEnd();
}
