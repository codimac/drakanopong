#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include "utils.h"
#include "level.h"
#include "elements.h"
#include "brick.h"

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
void loadLevel(Level * level) {
	FILE * file = NULL;
	char levelPath[20] = "./level/";
	int i = 0, j = 0;
	float x = -1, y = level->nbBrickY * BRICK_HEIGHT;
	strcat(levelPath,level->filename);
	file = fopen(levelPath,"r");
	if(file == NULL){
		exit(EXIT_FAILURE);
	}
	fscanf(file, "%d %d", &level->nbBrickX, &level->nbBrickY);
	level->nbBrickTotal = level->nbBrickX * level->nbBrickY;
	if(level->nbBrickTotal > MAX_BRICK) exit(EXIT_FAILURE);

	/* Each brick is stocked in the array */
	for(i = 0; i < level->nbBrickY ; i++){
		printf("\n row %d\n", i);
		y = convertPixelToMark( ((GAME_HEIGHT/2) - (level->nbBrickY * BRICK_HEIGHT)/2) + BRICK_HEIGHT*i , WINDOW_HEIGHT, axisY);
		for (j; j < (level->nbBrickX) *(i+1); j++) {
			x = convertPixelToMark( ( (j-i*level->nbBrickX)*BRICK_WIDTH ) + (WINDOW_WIDTH-GAME_WIDTH + BRICK_WIDTH)/2 , WINDOW_WIDTH, axisX );
			fscanf(file, "%d", &level->brick[j].type);
			initBrick(&level->brick[j], x, y);
			/*printf(" ------------- %d -------------\n", j);
			printf(" type %d \n", level->brick[j].type);
			printf("color : %.2f %.2f %.2f %.2f \n", level->brick[j].color.r, level->brick[j].color.g, level->brick[j].color.b,level->brick[j].color.alpha);
			*/
			printf("%.2f %.2f | ", level->brick[j].position.x, level->brick[j].position.y);
		}


	}
	displayConsole(*level);
	fclose(file);
}
void displayLevel(Level level){
	int i = 0, j = 0;
		for(i = 0; i < level.nbBrickTotal ; i++){
			displayBrick(level.brick[i]);
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
