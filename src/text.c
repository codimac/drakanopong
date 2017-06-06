#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "utils.h"
#include "text.h"
#include <SDL/SDL_ttf.h>
#include "texture.h"

void displayText(float x, float y, Text t){
	/*drawText(&t);*/
	glPushMatrix();
		glTranslatef(x, y, 0);
        texturedRectangle(t.id, convertCoordToMark(50, WINDOW_WIDTH), convertCoordToMark(50, WINDOW_HEIGHT));
    glPopMatrix();
}

void displayScore(int x, int y, Text t){
	float xpos = convertCoordToMark(x, WINDOW_WIDTH);
	float ypos = convertCoordToMark(y, WINDOW_HEIGHT);
	displayText(xpos, ypos, t);
}

void drawText(Text * t){
	glGenTextures(1, &t->id);
	int colors;
SDL_Color color={255,0,0};
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
	/*printf("text_surface->format->BytesPerPixel : %d\n", text_surface->format->BytesPerPixel );*/
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


    void updateScore(Text * score, int n, char * string){
    	sprintf(string, "%d",n);
    	strcpy(score->string, string);
    	strcpy(string, "0");
    }