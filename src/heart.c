#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "elements.h"
#include "heart.h"
#include "string.h"

	Heart initHeart(){
		Heart h;

		h.position.x = 0;
		h.position.y = 0;
		h.width = centeredPixelToMark(DEFAULT_WIDTH_HEART, WINDOW_WIDTH, axisX);
		h.height = centeredPixelToMark(DEFAULT_HEIGHT_HEART, WINDOW_HEIGHT, axisY);
		h.color.r = 1.0;
		h.color.g = 1.0;
		h.color.b = 1.0;
		h.color.alpha = 1.0;

		return h;
	}

	void setHeartPosition(Heart * h, int x, int y) {
		h->position.x = /*x*/convertCoordToMark(x, WINDOW_WIDTH);
		h->position.y = convertCoordToMark(y, WINDOW_HEIGHT);
	}

/*
	void displayHeart(Heart h, Texture t){
		glColor4f(h.color.r, h.color.g, h.color.b, h.color.alpha);
		glPushMatrix();
			glTranslatef(h.position.x, h.position.y, 0);
			rectangle(h.width, h.height);
		glPopMatrix();
	}*/

	void displayHeart(Heart h, Texture t){
			glPushMatrix();
    			glTranslatef(h.position.x, h.position.y, 0);
            	texturedRectangle(t.id, h.width, h.height);
    		glPopMatrix();
    }

    Texture initTextureHeart(char * path){
    	Texture t;
    	strcpy(t.path, path);
    	return t;
    }