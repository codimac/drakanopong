#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "elements.h"

Player initPlayer(char name, Bar b){
	Player P;
	P.name = name;
	P.lives = DEFAULT_HEARTS;
	P.score = 0;
	P.playerBar = b;
}
/**
 * move the ball
 * @method moveBall
 */
/*void moveBall(Ball ball) {

}*/

Bar initBar(){
	Bar b;

	b.position.x = 0;
	b.position.y = 0;
	b.speed.x = convertPixelToMark(10, WINDOW_WIDTH, axisX);
	b.speed.y = 0;
	b.size = centeredPixelToMark(100, WINDOW_WIDTH, axisX);
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


/**
 * move Bar depending on the player input
 * @method moveBar
 */

void moveBar(Player player, int direction) {
	return;
}

void displayBar(Bar b){
	float x = b.size;
	float y = convertPixelToMark(GAME_HEIGHT/2 - 4, GAME_HEIGHT, axisY);

	glPushMatrix();
	glTranslatef(b.position.x,b.position.y, 0);
	rectangle(b.size, y);
	glPopMatrix();
}
