#ifndef _GAME
#define _GAME

	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <SDL/SDL.h>
	#include "level.h"
	#include "elements.h"
	#include "bar.h"
	#include "player.h"
	#include "heart.h"
	#include <SDL/SDL.h>

	typedef enum Hardness{
		easy, normal, hardcore
	} Hardness;

	typedef enum GraphicTheme {
		dragon, retro
	} GraphicTheme;

	typedef struct Game {
		float width;
		float height;
		Level level;
		int IA;
		int graphicTheme;
		int hardness;
	} Game;


	void initGame(Game game);
	Game newGame();
	void drawGame();
	int exitGame();

	void animate(Ball * ball, float time, Player * player1, Player * player2);
	void displayPlayerHearts(Heart * h, Player player/*, float margin*/);
	Heart * initPlayerHearts(Player player);
	void setPlayerHearts(Heart * h, Player player, int x, int y, int margin, int side);

#endif
