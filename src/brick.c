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
    b->textureId = ID_BRICK + b->type;
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

void displayBrick(Brick b){
    if(b.display == 1){
    	glColor4f(b.color.r, b.color.g, b.color.b, b.color.alpha);
    	glPushMatrix();
    		glTranslatef(b.position.x, b.position.y, 0);
            texturedRectangle(b.textureId,centeredPixelToMark(BRICK_WIDTH, WINDOW_WIDTH, axisX), centeredPixelToMark(BRICK_HEIGHT, WINDOW_HEIGHT, axisY));
    		rectangle(centeredPixelToMark(BRICK_WIDTH, WINDOW_WIDTH, axisX) , centeredPixelToMark(BRICK_HEIGHT, WINDOW_HEIGHT, axisY));
    	glPopMatrix();
    }
}
