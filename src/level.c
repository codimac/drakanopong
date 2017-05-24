#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include "utils.h"
#include "level.h"
#include "elements.h"

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
	return level;
}

/* Load the chosen level from file
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

	/* Each brick is stocked in the array */
	for(i = 0; i < level.nbBrickTotal; i++) {
		fscanf(file, "%d", &brick[i]);
	}
	displayConsole(level, brick);


	

	fclose(file);
}

/*debug function. Display the type brick in console*/
void displayConsole(Level level, int brick[]){
	int i = 0, j = 0;
	printf("level : \n");
		for(i = 0; i < level.nbBrickY ; i++){
			for (j; j < (level.nbBrickX) *(i+1); j++) {
				printf(" %d ", brick[j]);
			}
			printf("\n");
		}
}
