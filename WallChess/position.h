#pragma once
#define calx(x) (2 * ((x) - 1)+1)
#define caly(y) (3 * ((y) - 1)+1)

class pos
{
public:
	pos();
	pos(int, int);

	void clp(int, int, int, int);
	pos operator[](int);
	bool operator==(const pos&);

	int x, y;
};