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
