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

	b->center.x = 0;
	b->center.y = 0;
	b->speed.x = convertPixelToMark(10, WINDOW_WIDTH, axisX);
	b->speed.y = 0;
	b->rayon = centeredPixelToMark(50, WINDOW_WIDTH, axisX);
	b->color.r = 1.0;
	b->color.g = 1.0;
	b->color.b = 1.0;
	b->color.alpha = 1.0;

	return b;
}

void displayBall(Ball * b){

	glPushMatrix();
		glTranslatef(b->center.x, b->center.y, 0);
		circle(b->rayon);
	glPopMatrix();
}

void setBallPosition(Ball * b, int x, int y) {
	b->center.x = convertPixelToMark(x, WINDOW_WIDTH, axisX);
	b->center.y = convertPixelToMark(y, WINDOW_HEIGHT, axisY);
}


/*void animateBallSpeed(float* alpha, int * direction){
	int i= 5;*/

	/*if(*alpha >= -45 || *alpha <= 45) direction = -direction;*/
	/*if (*alpha >= 45)
	{
		*direction = -1;
		*alpha += i * (*direction);
	}
	if (*alpha <=-45){
		*direction = 1;
		*alpha += i * (*direction);
	}

	if (*alpha < 45 && *alpha > -45) *alpha += i * (*direction);


}*/

void animateBallDirection(Ball * b, int * direction){
	int i = 1;
	
	/*
	if(b->center.x <= convertPixelToMark(5, WINDOW_WIDTH, axisX) || b->center.x >= convertPixelToMark(700, WINDOW_WIDTH, axisX) {
		direction = -direction;
	}*/

	if (b->center.x <= convertPixelToMark(50, WINDOW_WIDTH, axisX))
	{
		*direction = 1;
		b->center.x += convertPixelToMark((*direction)*i, WINDOW_WIDTH, axisX);
	}
	if ( b->center.x >= convertPixelToMark(700, WINDOW_WIDTH, axisX)){
		*direction = -1;
		b->center.x += convertPixelToMark((*direction)*i, WINDOW_WIDTH, axisX);
	}

	if(b->center.x > convertPixelToMark(50, WINDOW_WIDTH, axisX) && b->center.x < convertPixelToMark(700, WINDOW_WIDTH, axisX)) {
		b->center.x += convertPixelToMark((*direction)*i, WINDOW_WIDTH, axisX);
	}
	
}

void animateBallPosition(Ball * b){
	/*
	if (b->center.x <= WINDOW_WIDTH - b->rayon && b->center.x >= 0 + b->rayon){
		b->center.x +=5;
	}*/
	if (b->center.x > convertPixelToMark(5, WINDOW_WIDTH, axisX) && b->center.x < convertPixelToMark(700, WINDOW_WIDTH, axisX)){
		b->center.x += convertPixelToMark(5, WINDOW_WIDTH, axisX);
	}
}

/*
typedef struct Ball{
	Vector speed;
	float rayon;
	Color4f color;
} Ball;
*/