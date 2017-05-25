#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "elements.h"

Ball * initBall(){
	Ball * b;
	b = malloc(sizeof(Ball));
	if (b == NULL) {
		printf("not enough memory. Ball initialisation failed\n");
		exit(1);
	}

	b->center.x = convertCoordToMark(200, WINDOW_WIDTH);
	b->center.y = convertCoordToMark(150, WINDOW_HEIGHT);
	b->speed.x = convertCoordToMark(20, WINDOW_WIDTH);
	b->speed.y = convertCoordToMark(20, WINDOW_HEIGHT);
	b->rayon = convertCoordToMark(20, WINDOW_WIDTH);
	b->color.r = 1.0;
	b->color.g = 1.0;
	b->color.b = 1.0;
	b->color.alpha = 1.0;

	return b;
}

void displayBall(Ball * b){

	glPushMatrix();
		glTranslatef(b->center.x, b->center.y, 0);
		circle(b->rayon);/**/
	glPopMatrix();
}

void setBallPosition(Ball * b, int x, int y) {
	b->center.x = convertCoordToMark(x, WINDOW_WIDTH);
	b->center.y = convertCoordToMark(y, WINDOW_HEIGHT);
}


void animateBall(Ball * b, float time){

	b->center.x = b->center.x + b->speed.x * time;
	b->center.y = b->center.y + b->speed.y * time;
}
/*
int collision(Ball * b){
	if(b->center.x <= convertCoordToMark(-(float)WINDOW_WIDTH/2, WINDOW_WIDTH) 
		|| b->center.x >= convertCoordToMark((float)WINDOW_WIDTH/2, WINDOW_WIDTH)
		|| b->center.y <= convertCoordToMark(-(float)WINDOW_HEIGHT/2, WINDOW_HEIGHT)
		|| b->center.y >= convertCoordToMark((float)WINDOW_HEIGHT/2, WINDOW_HEIGHT)){
		return 1;
	}
	return 0;
}*/

int collision(Ball * b){
	if(b->center.x <= convertCoordToMark(-(float)WINDOW_WIDTH/2, WINDOW_WIDTH) 
		|| b->center.x >= convertCoordToMark((float)WINDOW_WIDTH/2, WINDOW_WIDTH)){
		return 1;
	}
	
	if(b->center.y <= convertCoordToMark(-(float)WINDOW_HEIGHT/2, WINDOW_HEIGHT)
		|| b->center.y >= convertCoordToMark((float)WINDOW_HEIGHT/2, WINDOW_HEIGHT)){
		return -1;
	}
	return 0;
}