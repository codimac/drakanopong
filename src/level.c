#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "utils.h"
#include "level.h"
#include "elements.h"
#include "game.h"

void setGameLevel(Level * level, char * gameLevel){
	strcpy(level->filename,"level" );
	strcat(level->filename, gameLevel);
	level->lvl = strtok(gameLevel, "_");
}

/* Init with the default level aka number 1*/
Level initLevel(){
	char gameLevel[5] = "_1";
	Level level;
	setGameLevel(&level, gameLevel);

/*	printf("lvl (string) : %s \n", gameLevel);
	printf("filename : %s \n", level.filename);
	printf("lvl (string) : %s \n", level.lvl);
*/
	return level;
}

/* Load the chosen level.
 *
 *
 */
void loadLevel(Level level) {
	FILE * file = NULL;
	int brick[MAX_BRICK];
	char levelPath[20] = "./level/";
	int i = 0, j = 0;
	strcat(levelPath,level.filename);
	file = fopen(levelPath,"r");
	if(file == NULL){
		exit(EXIT_FAILURE);
	}
	fscanf(file, "%d %d", &level.nbBrickX, &level.nbBrickY);

	level.nbBrickTotal = level.nbBrickX * level.nbBrickY;

	if(level.nbBrickTotal > MAX_BRICK) exit(EXIT_FAILURE);

	for(i = 0; i < level.nbBrickTotal; i++) {
		fscanf(file, "%d", &brick[i]);
	}
/*
	for(i = 0; i < level.nbBrickY ; i++){
		for (j; j < (level.nbBrickX) *(i+1); j++) {
			printf(" %d ", brick[j]);
		}
		printf("\n");
	}
*/

	fclose(file);
}
