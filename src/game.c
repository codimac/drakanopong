#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "game.h"
#include "bar.h"
#include "player.h"
#include "elements.h"
#include "utils.h"
#include "level.h"
#include "brick.h"
#include "texture.h"
#include "heart.h"
#include "ball.h"
#include "text.h"

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


playGame(Game game){
	if(-1 == TTF_Init()) {
			fprintf(stderr, "Impossible d'initialiser SDL_TTF. Fin du programme.\n");
			return EXIT_FAILURE;
	}
	int play = 1, end = 0;
	SDL_EnableKeyRepeat(10, 10); /* Value random. Need to read the doc ahah for more accurate value */

	/*
	 ****** LOAD LEVEL ******
	 */
		loadLevel(&game.level);
		loadBrickTexture(game.level.brickTextureId, game.level.nbTypeBrickUsed);

	/*
	 ****** LOAD LEVEL END ******
	 */


	/* INIT PLAYER ONE */
	Player player1 = initPlayer("Joueur 1");
	setBarPosition(&(player1.bar),WINDOW_WIDTH/2, MARGIN_BAR);

	/* INIT PLAYER TWO */
	Player player2 = initPlayer("Joueur 2");
	setBarPosition(&(player2.bar),WINDOW_WIDTH/2, WINDOW_HEIGHT-MARGIN_BAR);

	/*INIT BALLS*/
	Ball * ball1 = initBall();
	Ball * ball2 = initBall();
	setBallPosition(ball1, 0,0 /*-100, -100*/);
	setBallPosition(ball2, 0,0/*-300, -600*/);
	setBallDirection(ball1, DEFAULT_XDIR_BALL, DEFAULT_YDIR_BALL);
	setBallDirection(ball2, -DEFAULT_XDIR_BALL, -DEFAULT_YDIR_BALL);

	/*INIT PLAYER ONE'S HEARTS*/
	Heart * heart1 = initPlayerHearts(player1);
	setPlayerHearts(heart1, player1, WINDOW_WIDTH/2 - DEFAULT_XPOS_HEART, WINDOW_HEIGHT/2 - DEFAULT_YPOS_HEART, DEFAULT_MARGIN_HEART, -1);

	/*INIT PLAYER TWO'S HEARTS*/
	Heart * heart2 = initPlayerHearts(player2);
	setPlayerHearts(heart2, player2, DEFAULT_XPOS_HEART - WINDOW_WIDTH/2, DEFAULT_YPOS_HEART - WINDOW_HEIGHT/2, DEFAULT_MARGIN_HEART, 1);

	/*LOAD HEARTS TEXTURE*/
	Texture t_heart1;
	Texture t_heart2;
	t_heart1 = initTextureHeart("./assets/textures/hearts/h_1.png");
	t_heart2 = initTextureHeart("./assets/textures/hearts/h_2.png");
	loadTexture(&t_heart1);
	loadTexture(&t_heart2);

	/*INIT SCORE*/
	int scoreMax = 60;
	Text * scoreTab = initTextTab(scoreMax);
	loadTexts(scoreTab, scoreMax);


	Uint8 *keystates = SDL_GetKeyState(NULL);

	/************************
	 *    GAME MAIN LOOP    *
	 ***********************/
	while(play) {
		Uint32 startTime = SDL_GetTicks();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		/* affichage */
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.7,0.3,0.2); /* random color bonjour.*/

		/* TEMPORARY GAME FRAME */
		rectangle(game.width, game.height);

		/* Display Both Player Bar */
		displayBar(player1.bar);
		displayBar(player2.bar);
		/*initGame(game);*/
		float time = 0.2;
		animate(ball1, time, &player1, &player2);
		animate(ball2, time, &player1, &player2);
		hideBricks(ball1, &(game.level), &player1, &player2);
		hideBricks(ball2, &(game.level), &player1, &player2);

		/* Display Bricks */
		glColor3f(0.3,0.3,0.2);
		displayLevel(game.level);
		/*DISPLAY LIVES*/
		displayPlayerHearts(heart1, player1, t_heart1);
		displayPlayerHearts(heart2, player2, t_heart2);

		/*DISPLAY SCORES*/
		if(player1.score >= 0 && player1.score < scoreMax){
			displayScore(-300, 180, 25, 25, scoreTab[player1.score]); /* pb : player1. score*/
		}
		if(player2.score >= 0 && player1.score < scoreMax){
			displayScore(300, -180, 25, 25, scoreTab[player2.score]); /* pb : player1. score*/
		}

		SDL_GL_SwapBuffers();
		/* ****** */


		SDL_PumpEvents(); /* update the keystates array */

		/*PLayer 1*/
		if(keystates[SDLK_e]) {
			moveBar(&(player1.bar), right);
		} else if(keystates[SDLK_a]) {
			moveBar(&(player1.bar), left);
		}

		/*PLayer 2*/
		if(keystates[SDLK_RIGHT]) {
			moveBar(&(player2.bar), right);
		} else if(keystates[SDLK_LEFT]) {
			moveBar(&(player2.bar), left);
		}


		play =  gameWinner(player1, player2, &end);
		play = exitGame();
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if(elapsedTime < FRAMERATE_MILLISECONDS) {
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
		if(end !=0) {
			play = 0;
		}
	}

	if(end !=0){
		displayWinner(end);
	}
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

		default :
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
