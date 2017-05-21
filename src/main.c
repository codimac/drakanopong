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
		Bar bar = initBar();
		int loop = 1;
		SDL_EnableKeyRepeat(10, 10);
		while(loop) {
			Uint32 startTime = SDL_GetTicks();

			/* affichage */
			glClear(GL_COLOR_BUFFER_BIT);


			/*initGame(game);*/
			/*displayBar(bar);*/

			SDL_GL_SwapBuffers();
			/* ****** */

			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				if(e.type == SDL_QUIT) {
					loop = 0;
					break;
				}
				switch(e.type) {
					case SDL_VIDEORESIZE:
						WINDOW_WIDTH = e.resize.w;
						WINDOW_HEIGHT = e.resize.h;
						setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
						break;

					case SDL_KEYDOWN:
						if (e.key.keysym.sym == 'q' || e.key.keysym.sym == SDLK_ESCAPE) {
							loop = 0;
						}
						if (e.key.keysym.sym == 'a' || e.key.keysym.sym == SDLK_LEFT) {
							moveBar(&bar, left);
						}
						if (e.key.keysym.sym == 'e' || e.key.keysym.sym == SDLK_RIGHT) {
							moveBar(&bar, right);
						}
						break;

					default:
						break;
				}
			}

			Uint32 elapsedTime = SDL_GetTicks() - startTime;
			if(elapsedTime < FRAMERATE_MILLISECONDS) {
				SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
			}
		}

		/*let's play*/
		int play = 1;
		/* INIT PLAYER ONE */
 		Player player1 = initPlayer("Joueur 1");
		setBarPosition(&(player1.bar),WINDOW_WIDTH/2, MARGIN_BAR);

		/* INIT PLAYER TWO */
		Player player2 = initPlayer("Joueur 2");;
		/*if(game.IA == 1){*/
			/*player2.name = "THE IA \0"; /* why not */
		/*}*/
		setBarPosition(&(player2.bar),WINDOW_WIDTH/2, WINDOW_HEIGHT-MARGIN_BAR);

		while(play) {
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			/* affichage */
			glClear(GL_COLOR_BUFFER_BIT);

			/*initGame(game);*/
			displayBar(player1.bar);
			displayBar(player2.bar);

			SDL_GL_SwapBuffers();
			/* ****** */

			Uint8 *keystates = SDL_GetKeyState(NULL);
			if(keystates[SDLK_q]){
				play = 0;
			}
			if(keystates[SDLK_RIGHT]) {
				moveBar(&bar, right);
			} else if(keystates[SDLK_LEFT]) {
				moveBar(&bar, left);
			}
		}

		SDL_Quit();

		return EXIT_SUCCESS;
}
