#include <stdlib.h>
#include <time.h>
#include "Gamespace.h"


int main()
{
	srand(time(NULL));

	Gamespace GS;

	std::cout << GS;

	GS.play();

	return 0;
}