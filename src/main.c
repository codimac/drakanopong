#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

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
#include <SDL/SDL_ttf.h>

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape(unsigned int width, unsigned int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1., 1., -1., 1.);
}

void setVideoMode(unsigned int width, unsigned int height) {
	if(NULL == SDL_SetVideoMode(width, height, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		exit(EXIT_FAILURE);
	}

	reshape(width, height);
}

int main(int argc, char** argv) {

		if(-1 == TTF_Init()) {
				fprintf(stderr, "Impossible d'initialiser SDL_TTF. Fin du programme.\n");
				return EXIT_FAILURE;
		}

		if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
				fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
				return EXIT_FAILURE;
		}
		
		setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
		SDL_WM_SetCaption("DRAKANOPONG", NULL);
		/* Create the game with default value*/
		Game game = newGame();

		/*INIT BALLS*/
		Ball * ball1 = initBall();
		Ball * ball2 = initBall();
		setBallPosition(ball1, 0,0 /*-100, -100*/);
		setBallPosition(ball2, 0,0/*-300, -600*/);
		setBallDirection(ball1, DEFAULT_XDIR_BALL, DEFAULT_YDIR_BALL);
		setBallDirection(ball2, -DEFAULT_XDIR_BALL, -DEFAULT_YDIR_BALL);

		SDL_EnableKeyRepeat(10, 10); /* Value random. Need to read the doc ahah for more accurate value */

		/* MENU LOOP */
		/* we don't have a menu yet. */

		/*GAME START*/

		int play = 1, end = 0;
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
		if(game.IA == 1){
			player2.name = "THE IA \0"; /* why not */
		}

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
		int scoreMax = 50;
		Text * scoreTab = initTextTab(scoreMax);
		loadTexts(scoreTab, scoreMax);

		setBarPosition(&(player2.bar),WINDOW_WIDTH/2, WINDOW_HEIGHT-MARGIN_BAR);
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



		}

		if(end !=0){
			glColor3f(0.,0.,0.);
			rectangle(-1.,-1.);
			Texture winner;
			int loop = 1;
			sprintf(winner.path,"./assets/textures/winner/winner_%d.png", end);
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

		SDL_Quit();

		/*glDeleteTextures(game.level.nbTypeBrickUsed, game.level.brickTextureId[0].id);*/
		destroyBrickTexture(game.level.brickTextureId, game.level.nbTypeBrickUsed);
		destroyBrickTexture(scoreTab, scoreMax);
		glDeleteTextures(1, t_heart1.id);
		glDeleteTextures(1, t_heart2.id);
		return EXIT_SUCCESS;
}
