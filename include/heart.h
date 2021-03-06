#ifndef _HEART
#define _HEART
	#include <stdlib.h>
	#include <stdio.h>
	#include <math.h>
	#include <GL/gl.h>
	#include "elements.h"
	#include "texture.h"
	#include "utils.h"

	static unsigned int DEFAULT_WIDTH_HEART = 40;
	static unsigned int DEFAULT_HEIGHT_HEART = 40;
	static unsigned int DEFAULT_XPOS_HEART = 20;
	static unsigned int DEFAULT_YPOS_HEART = 20;
	static unsigned int DEFAULT_MARGIN_HEART = 10;
	static unsigned int DEFAULT_MAX_LIVES = 10;
	/*static unsigned int DEFAULT_HEARTS = 10;*/

	typedef struct Heart {
		Point position;
		float width, height;
		GLuint textureId;
		Color4f color;
	} Heart;

	Heart initHeart();
	void displayHeart(const Heart h, Texture t);
	void deleteHeart(Heart * h);
	void setHeartPosition(Heart * h, int x, int y);
	Texture initTextureHeart(char * path);

#endif
