#ifndef _GAME
#define _GAME

	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <SDL/SDL.h>
	#include "elements.h"
	#include "bar.h"
	#include "level.h"

	typedef enum Hardness{
		easy, normal, hardcore
	} Hardness;

	typedef enum GraphicTheme {
		dragon, retro
	} GraphicTheme;

	typedef struct Game {
		float width;
		float height;
		char lvl[5];
		/*Level level;*/
		int IA;
		int graphicTheme;
		int hardness;
	} Game;

	void initGame(Game game);
	Game newGame();
	void drawGame();
	int exitGame();

#endif
