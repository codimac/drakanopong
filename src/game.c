#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include "game.h"
#include "bar.h"
#include "player.h"
#include "elements.h"
#include "ball.h"
#include "level.h"
#include "texture.h"

static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

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
/*
 * Detect if someone lost.
 */
int gameWinner(Player player1, Player player2, int *end) {
	if(player1.lives == 0) {
		*end = 1;
		return 0;
	} else if (player2.lives == 0) {
		*end = 2;
		return 0;
	} else {
		return 1;
	}
}
/*
 * display on screen the winner (don't take into consideration the score yet)
 */
void displayWinner(int playerWin) {
	glColor3f(0.,0.,0.);
	rectangle(-1.,-1.);
	Texture winner;
	int loop = 1;
	sprintf(winner.path,"./assets/textures/winner/winner_%d.png", playerWin);
	loadTexture(&winner);
	printf("%d\n", winner.id);
	while(loop) {
		texturedRectangle(winner.id,-0.5, 0.5);
		Uint32 startTime = SDL_GetTicks();
		loop = exitGame();
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if(elapsedTime < FRAMERATE_MILLISECONDS) {
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
		SDL_GL_SwapBuffers();
	}
}

int mainMenu(){
	int loop = 1, lvl = 1;
	while(loop) {
		Uint32 startTime = SDL_GetTicks();

		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				loop = 0;
				break;
			}
			switch(e.type) {
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == 'q' || e.key.keysym.sym == SDLK_ESCAPE) {
						return -1;
					}
					if(e.key.keysym.sym == SDLK_UP){
						if(lvl == 1) {
							lvl = NB_LVL;
						} else {
							lvl --;
						}
						printf("%d\n", lvl);
					}
					if(e.key.keysym.sym == SDLK_DOWN){
						if(lvl == NB_LVL) {
							lvl = 1;
						} else {
							lvl ++;
						}
						printf("%d\n", lvl);
					}
					if(e.key.keysym.sym == SDLK_KP_ENTER||e.key.keysym.sym == SDLK_RIGHT){
						return lvl;
					}
					break;
			}
		}
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if(elapsedTime < FRAMERATE_MILLISECONDS) {
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
		SDL_GL_SwapBuffers();
	}
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
			ball->lastBar = 1;
		}
		break;

		case -2 :{
			ball->center.y = player2->bar.position.y + y + ball->radius;
			ball->speed.y = -ball->speed.y;
			ball->lastBar = 2;
		}
		break;

		case -1 : {
			ball->lastBar = 0;
			setBallPosition(ball, -DEFAULT_XPOS_BALL, -DEFAULT_YPOS_BALL);
			setBallDirection(ball, -DEFAULT_XDIR_BALL, -DEFAULT_YDIR_BALL);
			if (player2->lives != 0){
				player2->lives--;
			}
		}
		break;

		case 1 : {
			ball->lastBar = 0;
			setBallPosition(ball, DEFAULT_XPOS_BALL, DEFAULT_YPOS_BALL);
			setBallDirection(ball, DEFAULT_XDIR_BALL, DEFAULT_YDIR_BALL);
			if (player1->lives != 0){
				player1->lives--;
			}
		}
		break;

		default :;
		break;
	}

	animateBall(ball, time);
	displayBall(ball);
}


	void displayPlayerHearts(Heart * h, Player player, Texture texture){
		int i;
		for (i=0; i < player.lives; i++){
			displayHeart(h[i], texture);
		}
	}

	Heart * initPlayerHearts(Player player){
		int i;
		Heart * h;
		h = malloc(sizeof(Heart)*player.lives);
		for (i=0; i < player.lives; i++){
			h[i] = initHeart();
		}

		return h;
	}

	/*side = 1 for left, -1 for right*/

	void setPlayerHearts(Heart * h, Player player, int x, int y, int margin, int side){
		int i,j;
		int nb_columns = (WINDOW_WIDTH - GAME_WIDTH  - 2*margin) / ((DEFAULT_WIDTH_HEART + margin)*2);
		int nb_rows = player.lives / nb_columns;
		int rest = player.lives % nb_columns;
		margin = margin * side;

		for(i = 0; i < nb_rows; i++){
			for (j = 0; j < nb_columns; j++){
					setHeartPosition(&h[i*nb_columns+j], (x + side*DEFAULT_WIDTH_HEART*j + (j+1)*margin), y);
			}
			y += margin + side * DEFAULT_HEIGHT_HEART;
		}

		if (rest != 0){
			i = nb_rows;
			for (j = 0; j < rest; j++){
					setHeartPosition(&h[i*nb_columns+j], x + side * DEFAULT_WIDTH_HEART*j + (j+1)*margin, y);
			}
		}
	}

	void hideBricks(Ball * ball, Level * level, Player * player1, Player * player2){
		int k = brickIndex(*ball, *level);
		float hBrick = convertCoordToMark(BRICK_HEIGHT, WINDOW_HEIGHT);

		if(brickArea(*ball, *level)){
			switch(collisionBrick(*ball, *level, k)){
				case 0 :;
				break;
				case 1 : {
					if(level->brick[k].durability <= 0){
						level->brick[k].display = 0;
					}
					else {
						level->brick[k].durability -=1;
					}
					ball->center.y = level->brick[k].position.y + hBrick + ball->radius;
					ball->speed.y = -ball->speed.y;
					player1->score += 1;
					testBonus(level->brick[k], player1);

				}
				break;
				case 2 : {
					if(level->brick[k].durability <= 0){
						level->brick[k].display = 0;
					}
					else {
						level->brick[k].durability -=1;
					}
					ball->center.y = level->brick[k].position.y - hBrick - ball->radius;
					ball->speed.y = -ball->speed.y;
					player2->score += 1;
					testBonus(level->brick[k], player2);
				}
				break;
				default :
					break;
			}
		}
	}


	void testBonus(Brick brick, Player * player){
		switch(brick.type){
			case ELIXIR :
				if(player->lives < DEFAULT_HEARTS){
					player->lives+=1;
				}
				break;
			case EXPAND_PLAYER_BAR:
				updateSizeBar(&(player->bar), 2);
				break;
			case WALL :
			case HIDDEN :
			case BASIC :
				break;
			default :
				break;
		}
	}
