#ifndef _TEXTURE
#define _TEXTURE
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
	#include <GL/glut.h>
	#include <GL/glu.h>
	#include <GL/gl.h>


	typedef struct Texture{
		GLuint id;
		char path[100];
	} Texture;

	#define TEXTURE(id) (Texture){ 0 }

	void loadTexture(Texture *t);
	void texturedRectangle(GLuint textureId,float x, float y);
	void deleteTextures(Texture t[], int nbTexture);
#endif
