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
		if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
				fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
				return EXIT_FAILURE;
		}

		setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
		SDL_WM_SetCaption("DRAKANOPONG", NULL);
		/* Create the game with default value*/
		Game game = newGame();
		Ball * ball = initBall();
		/*setBallPosition(ball, 400, 225);*/
		float time= 5;

		SDL_EnableKeyRepeat(10, 10); /* Value random. Need to read the doc ahah for more accurate value */

		/* MENU LOOP */
		/* we don't have a menu yet. */

		/*GAME START*/

		int play = 1;

		Ball * ball = initBall();
		/*setBallPosition(ball, 400, 225);*/


		/* INIT PLAYER ONE */
 		Player player1 = initPlayer("Joueur 1");
		setBarPosition(&(player1.bar),WINDOW_WIDTH/2, MARGIN_BAR);

		/* INIT PLAYER TWO */
		Player player2 = initPlayer("Joueur 2");
		if(game.IA == 1){
			player2.name = "THE IA \0"; /* why not */
		}
		setBarPosition(&(player2.bar),WINDOW_WIDTH/2, WINDOW_HEIGHT-MARGIN_BAR);
		Uint8 *keystates = SDL_GetKeyState(NULL);

		while(play) {
			Uint32 startTime = SDL_GetTicks();

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			/* affichage */
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(0.7,0.3,0.2); /* random color bonjour.*/

			rectangle(game.width, game.height);
			/*initGame(game);*/

			displayBar(player1.bar);
			displayBar(player2.bar);
			/*initGame(game);*/
			float time = 1;
			animate(ball, time);

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

			play = exitGame();


			Uint32 elapsedTime = SDL_GetTicks() - startTime;
			if(elapsedTime < FRAMERATE_MILLISECONDS) {
				SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
			}
		}

		SDL_Quit();

		return EXIT_SUCCESS;
}
