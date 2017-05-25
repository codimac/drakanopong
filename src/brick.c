#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include "utils.h"
#include "elements.h"
#include "brick.h"

void initBrick(Brick *b){
    if(b->type!=EMPTY||b->type!=HIDDEN){
        b->display = 1;
    } else {
        b->display = 0;
    }
    


}
void displayBrick(Brick b){
    if(b.display = 1){
    	glColor4f(b.color.r,b.color.g,b.color.b, b.color.alpha);
    	glPushMatrix();
    		glTranslatef(b.position.x,b.position.y, 0);
    		rectangle(0.1, 0.1);
    	glPopMatrix();
    }
}
