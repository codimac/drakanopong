#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

/**
 * int axis : 1 for width, -1 for height
 * int mark : WINDOW_WIDTH / WINDOW_HEIGHT / GAME_WIDTH / GAME_HEIGHT ...
 * return float value between -1 and 1
**/
float convertPixelToMark(int pixel, int mark, int axis){
	return axis*(-1+2*pixel/mark);
}
