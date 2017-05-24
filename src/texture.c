#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include "texture.h"

void loadTexture(char path){
	SDL_Surface* img = IMG_Load(path);
	if(img != NULL){
	    GLenum format;
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
			    fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", path);
			    exit(EXIT_FAILURE);
		}
	}
}
