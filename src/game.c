#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"
#include "bar.h"
#include "player.h"
#include "elements.h"
#include "level.h"

/**
 * create a default game settings
 **/
Game newGame(){
	Game G;
	G.width = centeredPixelToMark(GAME_WIDTH, WINDOW_WIDTH, axisX);
	G.height = convertPixelToMark(GAME_HEIGHT, WINDOW_HEIGHT, axisY);
	strcpy(G.lvl, "_11");
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
