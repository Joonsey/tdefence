#include "types.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// retrieves distance between points. 0 means they are on top eachother
// and can therefore be used to figure it out if they are
// 'equal'
int cmp_point(Point a, Point b) {
	return (int)sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Point sub_point(Point a, Point b) {
	return (Point){a.x - b.x, a.y - b.y};
}

Point add_point(Point a, Point b) {
	return (Point){a.x + b.x, a.y + b.y};
}

Point mul_point(Point a, Point b) {
	return (Point){a.x * b.x, a.y * b.y};
}

Point div_point(Point a, Point b) {
	if (a.x == 0 & b.y == 0) {
		printf("ERROR: division by zero\n");
		exit(1);
	}
	return (Point){a.x / b.x, a.y / b.y};
}
