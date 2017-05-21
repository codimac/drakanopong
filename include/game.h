#ifndef _GAME
#define _GAME

	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include "elements.h"
	#include "bar.h"
	#include <SDL/SDL.h>

	typedef enum Hardness{
		easy, normal, hardcore
	} Hardness;

	typedef enum GraphicTheme {
		dragon, retro
	} GraphicTheme;

	typedef struct Game {
		int lvl;
		int IA;
		int graphicTheme;
		int hardness;
	} Game;

	void initGame(Game game);
	Game newGame();
	void drawGame();

#endif
