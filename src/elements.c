#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "elements.h"

/**
 * move the ball
 * @method moveBall
 */
/*void moveBall(Ball ball) {

}*/

Bar initBar(){
	Bar b;
	b.size = convertPixelToMark(GAME_WIDTH/2 - 25, GAME_WIDTH, axisX);

	b.position.x = 0;
	b.position.y = 0;

	b.color.r = 1.0;
	b.color.g = 1.0;
	b.color.b = 1.0;

	return b;
}


/**
 * move Bar depending on the player input
 * @method moveBar
 */
 /*
void moveBar(Player player, int direction) {
	return;
}*/

void displayBar(Bar b){
	float y = convertPixelToMark(GAME_HEIGHT/2 - 4, GAME_HEIGHT, axisY);
	rectangle(b.size, y);
}
