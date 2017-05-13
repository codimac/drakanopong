#include <stdlib.h>
#include <stdio.h>

typedef enum Axis{
	axisX = 1, axisY = -1
}Axis;

float convertPixelToMark(int pixel, int mark, int axis);
void rectangle(float width, float height);
