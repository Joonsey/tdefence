#include "types.h"
#include "stdio.h"
#include "math.h"

int cmp_point(Point a, Point b) {
	return (int)sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
