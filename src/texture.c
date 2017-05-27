#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include "texture.h"

void loadTexture(Texture t){
	glGenTextures(1,&(t.id));

	SDL_Surface* img = IMG_Load(t.path);
	if(img == NULL) {
		printf("null\n");
		exit(EXIT_FAILURE);
	}
	GLenum format;
	if(img != NULL){
	    switch(img->format->BytesPerPixel) {
	    	case 1:
	      		format = GL_RED;
	      	break;
	      	case 3:
	      		format = GL_RGB;
	      	break;
	      	case 4:
	     		 format = GL_RGBA;
	      	break;
	      	default:
			    fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", t.path);
			    exit(EXIT_FAILURE);
		}
	}

	glBindTexture(GL_TEXTURE_2D,t.id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D( GL_TEXTURE_2D,0, GL_RGBA, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, img->pixels);
	SDL_FreeSurface(img);
}

void texturedRectangle(GLuint textureId,float x, float y){
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex2f(-x,-y);

		glTexCoord2f(1,1);
		glVertex2f(x,-y);

		glTexCoord2f(1,0);
		glVertex2f(x,y);

		glTexCoord2f(0,0);
		glVertex2f(-x,y);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void deleteTextures(Texture t[], int nbTexture){
	glDeleteTextures(nbTexture,&(t->id));
}
