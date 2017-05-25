#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include "utils.h"
#include "elements.h"
#include "brick.h"

void initBrick(Brick *b, float x, float y){
    b->display = 1;
    b->position.x = x;
    b->position.y = y;
    switch(b->type){
        case EMPTY:
        case HIDDEN:
            b->display = 0;
            printf("display null\n");
            break;
        case BASIC:
            b->durability = 1;
            b->color.r = 0.5;
            b->color.g = 0.;
            b->color.b = 0.7;
            break;
        case ELIXIR:
            b->durability = 1;
            b->color.r = 0.8;
            b->color.g = 0.1;
            b->color.b = 0.3;
            break;
        case EXPAND_PLAYER_BAR:
            b->durability = 1.;
            b->color.r = 0.1;
            b->color.g = 0.5;
            b->color.b = 1.;
            break;
        case WALL:
            b->durability = 1;
            b->color.r = 0.7;
            b->color.g = 0.2;
            b->color.b = 1.;
            break;
    }
    b->color.alpha = 1.0;
}

void displayBrick(Brick b){

        /*printf("color : %.2f %.2f %.2f %.2f \n", b.color.r, b.color.g, b.color.b,b.color.alpha);
        printf("position %.2f %.2f  \n", b.position.x, b.position.y);*/
    	glColor4f(b.color.r,b.color.g,b.color.b, b.color.alpha);
    	glPushMatrix();
    		glTranslatef(b.position.x,b.position.y, 0);
    		rectangle(centeredPixelToMark(BRICK_WIDTH, WINDOW_WIDTH, axisX) , centeredPixelToMark(BRICK_HEIGHT, WINDOW_HEIGHT, axisY));
    	glPopMatrix();

}
