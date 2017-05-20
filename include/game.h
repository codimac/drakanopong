#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "elements.h"

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
