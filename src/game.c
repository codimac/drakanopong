#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"

/**
 * create a default game settings
 **/
Game newGame(){
	Game G;
	G.lvl = 1;
	G.IA = 0;
	G.graphicTheme = dragon;
	G.hardness = easy;
	return G;
}

/**
 * Lance une partie
 * Sert à tester les fonctions pour l'instant
 **/
void initGame(Game game) {
	Player J1, J2;
	Bar b = initBar();
	setBarPosition(&b, 400, 550);	
	displayBar(b);
}

void animate(Ball * ball, int time){
	if(collision(ball)==1){
		ball->speed.x = -ball->speed.x;
	}
	if(collision(ball)==-1){
		ball->speed.y = -ball->speed.y;
	}
	animateBall(ball, time);
	displayBall(ball);
}