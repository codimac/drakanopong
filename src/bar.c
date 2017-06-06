#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "elements.h"
#include "bar.h"
#include "utils.h"

Bar initBar(){
	Bar b;

	b.position.x = 0;
	b.position.y = 0;
	b.speed.x = -centeredPixelToMark(DEFAULT_SPEED_BAR, WINDOW_WIDTH, axisX);
	b.speed.y = 0;
	b.size = centeredPixelToMark(DEFAULT_WIDTH_BAR, WINDOW_WIDTH, axisX);
	b.color.r = 1.0;
	b.color.g = 1.0;
	b.color.b = 1.0;
	b.color.alpha = 1.0;

	return b;
}

void setBarPosition(Bar *b, int x, int y) {
	b->position.x = convertPixelToMark(x, WINDOW_WIDTH, axisX);
	b->position.y = convertPixelToMark(y, WINDOW_HEIGHT, axisY);
}

/*
 * update the size of the bar
 */
void updateSizeBar(Bar *b, float mult){
	if(b->size >  centeredPixelToMark(3*DEFAULT_WIDTH_BAR, WINDOW_WIDTH, axisX)) {
		b->size = centeredPixelToMark(  mult * DEFAULT_WIDTH_BAR, WINDOW_WIDTH, axisX);
	}
}
/**
 * move Bar depending on the player input
 * @method moveBar
 */

void moveBar(Bar *b, int direction) {
	float border = centeredPixelToMark(GAME_WIDTH, WINDOW_WIDTH, axisX); /* -0.5 */
	switch (direction) {
		case left :
			if(b->position.x - b->speed.x > border - b->size ){
				b->position.x = b->position.x - b->speed.x ;
			}
			break;
		case right :
			if(b->position.x + b->speed.x < -border + b->size ){
				b->position.x = b->position.x + b->speed.x;
			}
			break;
	}
}

void displayBar(Bar b){
	float y = convertPixelToMark(GAME_HEIGHT/2 - 4, GAME_HEIGHT, axisY);
	glColor4f(b.color.r,b.color.g,b.color.b, b.color.alpha);
	glPushMatrix();
		glTranslatef(b.position.x,b.position.y, 0);
		rectangle(b.size, y);
	glPopMatrix();
}
