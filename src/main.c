#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

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

		SDL_EnableKeyRepeat(0, 0);

		/* MENU LOOP */
		/* we don't have a graphic menu yet.
		* Uncomment bellow to try to change the lvl. To see which level you are on, the terminal is your friend.
		* left arrow instead of enter to start playing
		*/
		/*
		int lvl = mainMenu();
		if(lvl == -1) {
			play = 0; /* empêche de la jeu de démarrer et quitte*/
		/*}

		char level[10];
		sprintf(level, "_%d", lvl);
		setGameLevel(&game.level, level );
		*/
		/*GAME START*/
		playGame(game);

		SDL_Quit();

		/*glDeleteTextures(game.level.nbTypeBrickUsed, game.level.brickTextureId[0].id);*/
	/*	destroyBrickTexture(game.level.brickTextureId, game.level.nbTypeBrickUsed);
		destroyBrickTexture(scoreTab, scoreMax);
		glDeleteTextures(1, t_heart1.id);
		glDeleteTextures(1, t_heart2.id); */
		return EXIT_SUCCESS;
}
