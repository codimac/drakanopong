#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"
#include "bar.h"
#include "player.h"
#include "elements.h"
#include "ball.h"
#include "level.h"

/**
 * create a default game settings
 **/
Game newGame(){
	Game G;
	G.width = centeredPixelToMark(GAME_WIDTH, WINDOW_WIDTH, axisX);
	G.height = convertPixelToMark(GAME_HEIGHT, WINDOW_HEIGHT, axisY);
	G.level = initLevel();
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


void drawGame(){
	Uint8 *keystates = SDL_GetKeyState(NULL);
}

int exitGame(){
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		if(e.type == SDL_QUIT) {
			return 0;
			break;
		}
		switch(e.type) {
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == 'q' || e.key.keysym.sym == SDLK_ESCAPE) {
					return 0;
				}
				break;

			default:
				return 1;
				break;
		}
	}
	return 1;
}

void animate(Ball * ball, float time, Player * player1, Player * player2){
	float y =  convertPixelToMark(GAME_HEIGHT/2 - 4, GAME_HEIGHT, axisY);
	switch(collision(ball, player1->bar, player2->bar)){

		case 3 : {
			ball->center.x = convertCoordToMark((float)GAME_WIDTH/2, WINDOW_WIDTH) - ball->radius;
			ball->speed.x = -ball->speed.x;
		}
		break;

		case -3 : {
			ball->center.x = convertCoordToMark(-(float)GAME_WIDTH/2, WINDOW_WIDTH) + ball->radius;
			ball->speed.x = -ball->speed.x;
		}
		break;

		case 2 :{
			ball->center.y = player1->bar.position.y - y - ball->radius;
			ball->speed.y = -ball->speed.y;
		}
		break;

		case -2 :{
			ball->center.y = player2->bar.position.y + y + ball->radius;
			ball->speed.y = -ball->speed.y;
		}
		break;

		case -1 : {
			setBallPosition(ball, DEFAULT_XPOS_BALL, DEFAULT_YPOS_BALL);
			if (player2->lives != 0){
				player2->lives--;
			}
		}
		break;

		case 1 : {
			setBallPosition(ball, DEFAULT_XPOS_BALL, DEFAULT_YPOS_BALL);
			if (player1->lives != 0){
				player1->lives--;
			}
		}
		break;

		default :
		break;
	}

	animateBall(ball, time);
	displayBall(ball);
}

/*
	void displayPlayerHearts(Heart * h, Player player, float margin){
		int i;
		for (i=0; i < player.lives; i++){

			/*if (i != 0){

				/*if (margin < 0){

					h[i].position.x = h[i-1].position.x - h[i-1].width;
				}
				else*/ /*h[i].position.x = h[i-1].position.x + h[i-1].width + 100;
			}*/
			/*(&(h[i]))->position.y += 100;
		}
	}*/

	Heart * initPlayerHearts(Player player){
		int i;
		Heart * h;
		h = malloc(sizeof(Heart)*player.lives);
		for (i=0; i < player.lives; i++){
			h[i] = initHeart();
		}

		return h;
	}

	void setPlayerHearts(Heart * h, Player player, int x, int y){
		int i;
		for (i=0; i < player.lives; i++){
			setHeartPosition(&h[i], x, y);
		}
	}



	/*
	void addHeart();
	void deleteheart();
	void freeHearts()*/
