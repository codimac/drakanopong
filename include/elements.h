#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "utils.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;
static unsigned int GAME_WIDTH = 400;
static unsigned int GAME_HEIGHT = 600;
static unsigned int DEFAULT_HEARTS = 5;

/* COULEUR */

typedef struct Color4f{
	float r, g, b, alpha;
} Color4f;

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
	Color4f color;
} Ball;

typedef struct Bar {
	Point position;
	Vector speed;
	float size;
	Color4f color;
} Bar;

typedef struct Brick {
	int type;
	int display;
	Color4f color;
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
