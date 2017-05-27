#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

#include <GL/glut.h>
#include <GL/glu.h>

#include "texture.h"

void loadTexture(Texture *t){
	glGenTextures(1,&(t->id));

	SDL_Surface* img = IMG_Load(t->path);
	if(img == NULL) {
		printf("null\n");
		exit(EXIT_FAILURE);
	}
	GLenum format;
	printf("img->format->BytesPerPixel : %d\n", img->format->BytesPerPixel );
	if(img != NULL){
	    switch(img->format->BytesPerPixel) {
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
			    fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", t->path);
			    exit(EXIT_FAILURE);
		}
	}

	glBindTexture(GL_TEXTURE_2D,t->id);
	glTexImage2D( GL_TEXTURE_2D,0, format, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(img);
	glBindTexture(GL_TEXTURE_2D,0);
}

void texturedRectangle(GLuint textureId,float x, float y){
	glColor3f(1.,1.,1.);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textureId);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex2f(x,-y);

		glTexCoord2f(1,1);
		glVertex2f(-x,-y);

		glTexCoord2f(1,0);
		glVertex2f(-x,y);

		glTexCoord2f(0,0);
		glVertex2f(x,y);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void deleteTextures(Texture t[], int nbTexture){
	glDeleteTextures(nbTexture,&(t->id));
}
