#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include "utils.h"
#include "level.h"
#include "elements.h"
#include "brick.h"


/* Init with the default level aka number 1*/
Level initLevel(){
	char gameLevel[5] = "_1";
	Level level;
	setGameLevel(&level, gameLevel);
	return level;
}

/*
 * Change the game level
 */
void setGameLevel(Level * level, char * gameLevel){
	strcpy(level->filename,"level" );
	strcat(level->filename, gameLevel);
	level->lvl = strtok(gameLevel, "_");
}

/*
 * Load the chosen level from file
 */
void loadLevel(Level * level) {
	FILE * file = NULL;
	char levelPath[20] = "./level/";
	int i = 0, j = 0, textureIndice = 0, textureUsed[NB_TYPE_BRICK];
	float x = -1, y = level->nbBrickY * BRICK_HEIGHT;
	level->nbTypeBrickUsed = 0;
	strcat(levelPath,level->filename);

	file = fopen(levelPath,"r");
	if(file == NULL) exit(EXIT_FAILURE);

	fscanf(file, "%d %d", &level->nbBrickX, &level->nbBrickY);
	level->nbBrickTotal = level->nbBrickX * level->nbBrickY;

	if(level->nbBrickTotal > MAX_BRICK) exit(EXIT_FAILURE);
	for(i=0; i<NB_TYPE_BRICK; i++) {
		textureUsed[i] = 0;
	}
	/* Each brick is stocked in the array */
	for(i = 0; i < level->nbBrickY ; i++){
		y = convertPixelToMark( ((GAME_HEIGHT/2) - (level->nbBrickY * BRICK_HEIGHT)/2) + BRICK_HEIGHT*i , WINDOW_HEIGHT, axisY);
		for (j; j < (level->nbBrickX) *(i+1); j++) {
			x = convertPixelToMark( ( (j-i*level->nbBrickX)*BRICK_WIDTH ) + (WINDOW_WIDTH-GAME_WIDTH + BRICK_WIDTH)/2 , WINDOW_WIDTH, axisX );
			fscanf(file, "%d", &level->brick[j].type);
			initBrick(&level->brick[j], x, y);
			if(textureUsed[level->brick[j].type - 1] == 0){
				textureUsed[level->brick[j].type - 1] = 1;
				sprintf(level->brickTextureId[level->nbTypeBrickUsed].path,"./assets/textures/bricks/b_%d.png", level->brick[j].type);
				level->nbTypeBrickUsed++;
			}
		}
	}
	displayConsole(*level);
	fclose(file);
}
void displayLevel(Level level){
	int i = 0;
		for(i = 0; i < level.nbBrickTotal ; i++){
			displayBrick(level.brickTextureId,level.brick[i]);
		}
}

/*debug function. Display the type brick in console*/
void displayConsole(Level level){
	int i = 0, j = 0;
	printf("level : \n");
		for(i = 0; i < level.nbBrickY ; i++){
			for (j; j < (level.nbBrickX) *(i+1); j++) {
				printf(" %d ", level.brick[j].type);
			}
			printf("\n");
		}
}
