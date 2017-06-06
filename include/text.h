#ifndef _TEXT
#define _TEXT
	#include <stdlib.h>
	#include <stdio.h>
	#include "elements.h"

	typedef struct Text{
		GLuint id;
		char string[100];
	} Text;

	void displayScore(int x, int y, Text t);
	void displayText(float x, float y, Text t);
	void drawText(Text * t);
	Text initText(char * string);
	void updateScore(Text * score, int n, char * string);
#endif
