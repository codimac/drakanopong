#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* COULEUR */

typedef struct Color3f{
	float r, g, b;
}


/* ELEMENTS */
typedef struct Point{
	float x, y;
} Point;

typedef struct Vector{
	float x, y;
} Vector;

typedef struct Ball{
	Point center; /*position*/
	Vecteur vitesse;
	float rayon;
	Color3f color;
} Ball;

typedef Bar {
	Point center;
	Color3f color;
} Bar;

typedef struct Brick {
	int type;
	int display = 1;
	Color3f color;
} Brick;

/* PLAYERS */
typedef struct Player {
	char name;
	int lives;
	int score;
	Bar playerBar;
}

/* ENUM */
typedef enum TypeBrick {
	basics, explosion
};

typedef enum direction {
	left, right, stop
};
