#ifndef _GAME
#define _GAME

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
		Level level;
		int IA;
		int graphicTheme;
		int hardness;
	} Game;


	void initGame(Game game);
	Game newGame();
	void playGame(Game game);
	int exitGame();

	void animate(Ball * ball, float time, Player * player1, Player * player2);
	void displayPlayerHearts(Heart * h, Player player, Texture texture);
	Heart * initPlayerHearts(Player player);
	void setPlayerHearts(Heart * h, Player player, int x, int y, int margin, int side);
	void hideBricks(Ball * ball, Level * level, Player * player1, Player * player2);

#endif
