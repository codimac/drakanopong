#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "elements.h"
#include "player.h"
#include "bar.h"

/*static unsigned int DEFAULT_HEARTS = 5;*/

Player initPlayer(char name[]){
	Player p;
	p.name = name;
	p.lives = DEFAULT_HEARTS;
	p.score = 0;
	p.bar = initBar();
	return p;
}

void updateLives(Player *p, int offset){
	p->lives += offset;
}
