#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include "utils.h"
#include "elements.h"
#include "brick.h"
#include "texture.h"

void initBrick(Brick *b, float x, float y){

    b->display = 1;
    b->position.x = x;
    b->position.y = y;
    b->textureId = b->type - 1;
    switch(b->type){
        case EMPTY:
        case HIDDEN:
            b->display = 0;
            break;
        case BASIC:
            b->durability = 1;
            break;
        case ELIXIR:
            b->durability = 1;
            break;
        case EXPAND_PLAYER_BAR:
            b->durability = 1.;
            break;
        case WALL:
            b->durability = 3;
            break;
        default:
            b->durability = 1;
            break;
    }
}

void displayBrick(Texture t[], Brick b){
    if(b.display == 1){
    	glPushMatrix();
    		glTranslatef(b.position.x, b.position.y, 0);
            texturedRectangle(t[b.textureId].id,centeredPixelToMark(BRICK_WIDTH, WINDOW_WIDTH, axisX), centeredPixelToMark(BRICK_HEIGHT, WINDOW_HEIGHT, axisY));
    	glPopMatrix();
    }
}

void loadBrickTexture(Texture t[], int nbBrickUsed){
    int i;
    for(i = 0; i < nbBrickUsed; i++){
        loadTexture(t[i]);
    }

}
void destroyBrickTexture(Texture t[], int nbBrickUsed){
    int i;
    for(i = 0; i < nbBrickUsed; i++){
        glDeleteTextures(1,t[i].id);
    }

}
