#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "elements.h"


/**
 * move the ball
 * @method moveBall
 */
void moveBall(Ball ball) {

}

Bar initBar(){
	Bar b;
	b.position.x = GAME_HEIGHT - 10;
	b.position.y = 10;
	b.size = -1+2*100/GAME_WIDTH;
	b.color.r = 1.0;
	b.color.g = 1.0;
	b.color.b = 1.0;
}
/**
 * move Bar depending on the player input
 * @method moveBar
 */
void moveBar(Player player, int direction) {

}
