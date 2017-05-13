#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

static unsigned int GAME_WIDTH = 600;
static unsigned int GAME_HEIGHT = 400;

/* COULEUR */

typedef struct Color3f{
	float r, g, b;
} Color3f;

/* ELEMENTS */
typedef struct Point{
	float x, y;
} Point;

typedef struct Vector{
	float x, y;
} Vector;

typedef struct Ball{
	Point center; /*position*/
	Vector speed;
	float rayon;
	Color3f color;
} Ball;

typedef struct Bar {
	Point position;
	Vector speed;
	float size;
	Color3f color;
} Bar;

typedef struct Brick {
	int type;
	int display;
	Color3f color;
} Brick;

/* PLAYERS */
typedef struct Player {
	char name;
	int lives;
	int score;
	Bar playerBar;
} Player;

/* ENUM */
typedef enum TypeBrick {
	basics, explosion
}TypeBrick;

typedef enum Direction {
	left, right, stop
} Direction;
/**
 * FUNCTIONS
 **/
Bar initBar();
void moveBar(Player player, int direction);
void displayBar(const Bar b);
