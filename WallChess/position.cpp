#include"position.h"
using namespace std;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

pos::pos(int _x, int _y) {
	x = _x;y = _y;
}

pos::pos() {
	x = y = 1;
}

void pos::clp(int minx, int maxx, int miny, int maxy) {
	if (x < minx)x = minx;
	if (x > maxx)x = maxx;
	if (y < miny)y = miny;
	if (y > maxy)y = maxy;
}

pos pos::operator[](int d) {
	pos b;
	b.x = x + dx[d];
	b.y = y + dy[d];
	return b;
}

bool pos::operator==(const pos& b) {
	return (x == b.x) && (y == b.y);
}