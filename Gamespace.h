#ifndef GAMESPACE_HEADER
#define GAMESPACE_HEADER
#include <iostream>

class Gamespace
{
	int value[4][4] = { 0 };
	int winState;
	int empty;
	int score;

public:
	Gamespace();

	void play();

	bool canMove();

	void stateCheck();

	void move(const char x);

	int createValue();

	void slideUp(int, int);
	void slideDown(int, int);
	void slideLeft(int, int);
	void slideRight(int, int);

	Gamespace& up();
	Gamespace& down();
	Gamespace& left();
	Gamespace& right();

	friend std::ostream& operator << (std::ostream&, const Gamespace&);
};

#endif GAMESPACE_HEADER
