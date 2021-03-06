#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "utils.h"
#include "text.h"
#include <SDL/SDL_ttf.h>
#include "texture.h"

void displayText(float x, float y, int width, int height, Text t){
	glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(180, 0, 1, 0);
        texturedRectangle(t.id, convertCoordToMark(width, WINDOW_WIDTH), convertCoordToMark(height, WINDOW_HEIGHT));
    glPopMatrix();
}

void displayScore(int x, int y, int width, int height, Text t){
	float xpos = convertCoordToMark(x, WINDOW_WIDTH);
	float ypos = convertCoordToMark(y, WINDOW_HEIGHT);
	displayText(xpos, ypos, width, height, t);
}

void drawText(Text * t){
	glGenTextures(1, &t->id);
	int colors;
SDL_Color color={255,255,0};
SDL_Surface * text_surface;
TTF_Font *font;
font = TTF_OpenFont("./assets/fonts/FreeSans.ttf", 10);
if (font == NULL){
	printf("Font is NULL");
	exit(EXIT_FAILURE);
}
if(!(text_surface=TTF_RenderUTF8_Blended(font,t->string,color))) {
	printf("TTF couldnt create texture");
	exit(EXIT_FAILURE);
}


colors = text_surface->format->BytesPerPixel;
	GLenum format;
	if(text_surface != NULL){
	    switch(text_surface->format->BytesPerPixel) {
	    	case 1:
	      		format = GL_ALPHA;
	      	break;
	      	case 3:
	      		format = GL_RGB;
	      	break;
	      	case 4:
	     		 format = GL_RGBA;
	      	break;
	      	default:
			    fprintf(stderr, "Format des pixels de l'image non pris en charge\n");
			    exit(EXIT_FAILURE);
		}
	}
	glBindTexture(GL_TEXTURE_2D,t->id);
	glTexImage2D( GL_TEXTURE_2D,0, colors/*format*/, text_surface->w, text_surface->h, 0, format, GL_UNSIGNED_BYTE, text_surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(text_surface);
	glBindTexture(GL_TEXTURE_2D,0);
}

    Text initText(char * string){
    	Text t;
    	strcpy(t.string, string);
    	return t;
    }

    Text * initTextTab(int scoreMax){
    	int i;
    	char * string;
    	Text * textTab;
    	textTab = malloc(sizeof(Text)*scoreMax);
    	if(textTab == NULL){
    		fprintf(stderr, "Couldn't Init TextTab\n");
    		exit(EXIT_FAILURE);
    	}
    	for(i=0; i < scoreMax; i++){
    		sprintf(string, "%d", i);
    		strcpy(textTab[i].string, string);
    	}
    	return textTab;
    }

    void loadTexts(Text * t, int scoreMax){
    	int i;
    	for(i=0; i< scoreMax; i++){
    		drawText(&(t[i]));
    	}
    }