#ifndef _TEXTURE
#define _TEXTURE
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include <SDL/SDL_image.h>

	#define ID_MENU_PRINCIPALE 0
	#define ID_MENU_LEVEL 100
	#define ID_MENU_THEME 200
	#define ID_MENU_HARDNESS 300
	#define ID_MENU_PLAYER 400
	#define ID_MENU_BEST_SCORE 500
	#define ID_BRICK 1000

	typedef struct Texture{
		GLuint id;
		char path[100];
	} Texture;

	#define TEXTURE(id) (Texture){ 0 }

	void loadTexture(Texture t);
	void texturedRectangle(GLuint textureId,float x, float y);
#endif
