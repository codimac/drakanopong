#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "elements.h"
#include "ball.h"

Ball * initBall(){
	Ball * b;
	b = malloc(sizeof(Ball));
	if (b == NULL) {
		printf("not enough memory. Ball initialisation failed\n");
		exit(1);
	}

	b->center.x = convertCoordToMark(10, WINDOW_WIDTH);
	b->center.y = convertCoordToMark(10, WINDOW_HEIGHT);
	b->speed.x = convertCoordToMark(20, WINDOW_WIDTH);
	b->speed.y = convertCoordToMark(20, WINDOW_HEIGHT);
	b->radius = convertCoordToMark(20, WINDOW_WIDTH);
	b->color.r = 1.0;
	b->color.g = 1.0;
	b->color.b = 1.0;
	b->color.alpha = 1.0;

	return b;
}

void displayBall(Ball * b){

	glPushMatrix();
		glTranslatef(b->center.x, b->center.y, 0);
		circle(b->radius);/**/
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


int collision(Ball * b, Bar bar1, Bar bar2){
	float y, x2, x1;
	x2 = bar2.size;
	x1 = bar1.size;
	y =  convertPixelToMark(GAME_HEIGHT/2 - 4, GAME_HEIGHT, axisY);

	if(x2 < 0) {
		x2 = - x2;
	}

	if(x1 < 0) {
		x1 = - x1;
	}

	if((b->center.x + b->radius) >= (bar1.position.x - x1)  && (b->center.x - b->radius) <= (bar1.position.x + x1) 
		&& (b->center.y + b->radius) >= (bar1.position.y - y)){
		return -2;
	}

	if((b->center.x + b->radius) >= (bar2.position.x - x2)  && (b->center.x - b->radius) <= (bar2.position.x + x2) 
		&& (b->center.y - b->radius) <= (bar2.position.y + y)){
		return -2;
	}

	if((b->center.x - b->radius) <= convertCoordToMark(-(float)GAME_WIDTH/2, WINDOW_WIDTH) 
		|| (b->center.x + b->radius) >= convertCoordToMark((float)GAME_WIDTH/2, WINDOW_WIDTH)){
		return 1;
	}

	if((b->center.y - b->radius) <= convertCoordToMark(-(float)GAME_HEIGHT/2, WINDOW_HEIGHT)
		|| (b->center.y + b->radius) >= convertCoordToMark((float)GAME_HEIGHT/2, WINDOW_HEIGHT)){
		return -1;
	}

	return 0;
}