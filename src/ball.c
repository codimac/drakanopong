#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "elements.h"
#include "ball.h"
#include "level.h"

Ball * initBall(){
	Ball * b;
	b = malloc(sizeof(Ball));
	if (b == NULL) {
		printf("not enough memory. Ball initialisation failed\n");
		exit(1);
	}

	b->center.x = convertCoordToMark(10, WINDOW_WIDTH);
	b->center.y = convertCoordToMark(10, WINDOW_HEIGHT);
	b->speed.x = convertCoordToMark(DEFAULT_XDIR_BALL, WINDOW_WIDTH);
	b->speed.y = convertCoordToMark(DEFAULT_YDIR_BALL, WINDOW_HEIGHT);
	b->radius = convertCoordToMark(20, WINDOW_WIDTH);
	b->color.r = 1.0;
	b->color.g = 1.0;
	b->color.b = 1.0;
	b->color.alpha = 1.0;
	b->lastBar = 0;

	return b;
}

void displayBall(Ball * b){

	glPushMatrix();
		glTranslatef(b->center.x, b->center.y, 0);
		circle(b->radius, b->color);
	glPopMatrix();
}

void setBallPosition(Ball * b, int x, int y) {
	b->center.x = convertCoordToMark(x, WINDOW_WIDTH);
	b->center.y = convertCoordToMark(y, WINDOW_HEIGHT);
}

void setBallDirection(Ball * b, int x, int y) {
	b->speed.x = convertCoordToMark(x, WINDOW_WIDTH);
	b->speed.y = convertCoordToMark(y, WINDOW_HEIGHT);
}

void animateBall(Ball * b, float time){

	b->center.x = b->center.x + b->speed.x * time;
	b->center.y = b->center.y + b->speed.y * time;
}

/*
 * Detect collisions between a ball and the player's bars
 * and between the ball and the game's borders.
 * Return int value.
 */
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

	/*If collision with player1's bar (top bar), return 2*/

	if((b->center.x + b->radius) >= (bar1.position.x - x1)  && (b->center.x - b->radius) <= (bar1.position.x + x1) 
		&& (b->center.y + b->radius) >= (bar1.position.y - y) && (b->center.y - b->radius) <= (bar1.position.y + y)){
		return 2;
	}

	/*If collision with player2's bar (bottom bar), return - 2*/

	if((b->center.x + b->radius) >= (bar2.position.x - x2)  && (b->center.x - b->radius) <= (bar2.position.x + x2) 
		&& (b->center.y - b->radius) <= (bar2.position.y + y) && (b->center.y + b->radius) >= (bar2.position.y - y)){
		return -2;
	}

	/*If collision with the game's lateral left border, return -3*/

	if((b->center.x - b->radius) <= convertCoordToMark(-(float)GAME_WIDTH/2, WINDOW_WIDTH)){
		return -3;
	}

	/*If collision with the game's lateral right border, return 3*/

	if((b->center.x + b->radius) >= convertCoordToMark((float)GAME_WIDTH/2, WINDOW_WIDTH)){
		return 3;
	}

	/*If collision with the game's bottom border, return -1*/

	if((b->center.y + b->radius) <= convertCoordToMark(-(float)GAME_HEIGHT/2, WINDOW_HEIGHT)){
		return -1;
	}

	/*If collision with the game's top border, return 1*/

	if((b->center.y - b->radius) >= convertCoordToMark((float)GAME_HEIGHT/2, WINDOW_HEIGHT)){
		return 1;
	}

	return 0;
}

int brickArea(Ball b, Level level){
	float hBrick = convertCoordToMark(BRICK_HEIGHT, WINDOW_HEIGHT);
	if(b.center.y - b.radius <= level.nbBrickY/2 * hBrick && b.center.y + b.radius >= - level.nbBrickY/2 * hBrick){
		return 1;
	}
	return 0;
}

int brickIndex(Ball b, Level level){
	float ballPointY;
	switch(b.lastBar){
		case 1 : ballPointY = b.center.y - b.radius;
		break;
		case 2 : ballPointY = b.center.y + b.radius;
		break;
		case 0 : ballPointY = 0;
		break;
		default : ballPointY = b.center.y;
	}
	float hBrick = convertCoordToMark(BRICK_HEIGHT, WINDOW_HEIGHT);
	float height_min = - level.nbBrickY/2 * hBrick;
	float h_span = (ballPointY - height_min)/ hBrick;
	int i = level.nbBrickY - h_span - 1;
	float wBrick = convertCoordToMark(BRICK_WIDTH, WINDOW_WIDTH);
	float w_span = ((b.center.x - convertCoordToMark(-(float)GAME_WIDTH/2, WINDOW_WIDTH)) / wBrick);
	int j = (int)w_span;
	int k = i * level.nbBrickX + j;
	
	return k;
}

int collisionBrick(Ball b, Level level, int k){
	if(k < 0 || k >= level.nbBrickY * level.nbBrickX){
		return 0;
	}

	if(level.brick[k].display == 0) return 0;

	switch(b.lastBar){
		case 1 : return 1;
		break;
		case 2 : return 2;
		break;
		case 0 : return 0;
		break;
		default : return 0;
	}
}