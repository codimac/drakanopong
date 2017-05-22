#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "utils.h"
#include "level.h"
#include "elements.h"
#include "game.h"

/*void setGameLevel(*Game game, char lvl){

}*/
Level initLevel(int lvl, char * filename){
	Level L;
	L.lvl = lvl;
	strcpy(L.filename, filename );
	return L;
}

void loadLevel(Game game){
	char filename[15];
	int lvl;
	Level level;

	strcpy(filename,"level" );
	strcat(filename, game.lvl);

	lvl = atoi(strtok(game.lvl, "_"));

	printf("lvl (string) : %s \n", game.lvl);
	printf("filename : %s \n", filename);
	printf("lvl (int) : %d \n", lvl);

	level = initLevel(lvl, filename);

}
