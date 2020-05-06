#include "Gamespace.h"

#include<conio.h>
#include <stdlib.h>

void swapsie(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Clear()
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}

Gamespace::Gamespace() : winState(0), empty(14), score(0)
{
	int* cell1 = &value[rand() % 4][rand() % 4];
	int* cell2;
	do
	{
		cell2 = &value[rand() % 4][rand() % 4];
	} while (cell2 == cell1);

	*cell1 = 2;

	*cell2 = 2 * (rand() % 2 + 1);
}

bool Gamespace::canMove()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ( i - 1 >= 0 && (value[i][j] == value[i - 1][j] || value[i - 1][j] == 0) ||
				i + 1 < 4 && (value[i][j] == value[i + 1][j] || value[i + 1][j] == 0) ||
				j - 1 >= 0 && (value[i][j] == value[i][j - 1] || value[i][j - 1] == 0) ||
				j + 1 < 4 && (value[i][j] == value[i][j + 1] || value[i][j + 1] == 0))

				return true;
		}
	}
	return false;
}

void Gamespace::stateCheck()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (value[i][j] == 2048)
			{
				winState = 1;
				return;
			}
		}
	}
	if (!canMove())
		winState = -1;
	return;
}

void Gamespace::play()
{
	char x;

	while (winState == 0)
	{
		do
		{
			x = _getch();
		} while (x != 'w' && x != 's' && x != 'a' && x != 'd' && x != 27);

		if (x == 27) // For ESC
			break;

		move(x);
		std::cout << *this;
		
		stateCheck();
	}

	if (winState == 1)
	{
		std::cout << "YOU WIN!";
		return;
	}

	std::cout << *this << "KUR, BACE";
	return;
}

int Gamespace::createValue()
{
	int parameter = (rand() % 10);
	if (parameter < 9) return 2;
	if (parameter == 9) return 4;
}

void Gamespace::move(const char x)
{
	if (x == 'w') up();
	else if (x == 's') down();
	else if (x == 'a') left();
	else right();

	if (empty != 0)
	{
		int* cell;
		do
		{
			cell = &value[rand() % 4][rand() % 4];
		} while (*cell != 0 && winState == 0);

		empty--;
		//*cell = 2 * (rand() % 2 + 1);
		*cell = createValue();
	}
}

void Gamespace::slideUp(int i, int j)
{
	while (i > 0 && value[i - 1][j] == 0 )
	{
		swapsie(value[i][j], value[i - 1][j]);
		i--;
	}

	if (i > 0 && value[i - 1][j] == value[i][j] && value[i][j] != 0)
	{
		value[i - 1][j] *= 2;
		score += value[i - 1][j];
		value[i][j] = 0;
		empty++;
	}

}

void Gamespace::slideDown(int i, int j)
{
	while (i < 3 && value[i + 1][j] == 0)
	{
		swapsie(value[i][j], value[i + 1][j]);
		i++;
	}

	if (i < 3 && value[i + 1][j] == value[i][j] && value[i][j] != 0)
	{
		value[i + 1][j] *= 2;
		score += value[i + 1][j];
		value[i][j] = 0;
		empty++;
	}
}

void Gamespace::slideLeft(int i, int j)
{
	while (j > 0 && value[i][j - 1] == 0)
	{
		swapsie(value[i][j], value[i][j - 1]);
		j--;
	}

	if (j > 0 && value[i][j - 1] == value[i][j] && value[i][j] != 0)
	{
		value[i][j - 1] *= 2;
		score += value[i][j - 1];
		value[i][j] = 0;
		empty++;
	}
}

void Gamespace::slideRight(int i, int j)
{
	while (j < 3 && value[i][j + 1] == 0)
	{
		swapsie(value[i][j], value[i][j + 1]);
		j++;
	}

	if (j < 3 && value[i][j + 1] == value[i][j] && value[i][j] != 0)
	{
		value[i][j + 1] *= 2;
		score += value[i][j + 1];
		value[i][j] = 0;
		empty++;
	}
}

Gamespace& Gamespace::up()
{
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (value[i][j] != 0)
			{
				slideUp(i, j);
			}
		}
	}

	return *this;
}

Gamespace& Gamespace::down()
{
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (value[i][j] != 0)
			{
				slideDown(i, j);
			}
		}
	}

	return *this;
}

Gamespace& Gamespace::left()
{
	for (int j = 1; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (value[i][j] != 0)
			{
				slideLeft(i, j);
			}
		}
	}

	return *this;
}

Gamespace& Gamespace::right()
{
	for (int j = 2; j >= 0; j--)
	{
		for (int i = 0; i < 4; i++)
		{
			if (value[i][j] != 0)
			{
				slideRight(i, j);
			}
		}
	}

	return *this;
}


std::ostream& operator << (std::ostream& os, const Gamespace& GS)
{
	Clear();

	os << "Score: " << GS.score << "\n+-----+-----+-----+-----+\n";

	for (int i = 0; i < 4; i++)
	{
		if (GS.value[i][0] < 10) os << "|  " << GS.value[i][0] << "  |";
		else if (GS.value[i][0] < 100) os << "|  " << GS.value[i][0] << " |";
		else if (GS.value[i][0] < 1000) os << "| " << GS.value[i][0] << " |";
		else os << "| " << GS.value[i][0] << "|";

		for (int j = 1; j < 4; j++)
		{
			if (GS.value[i][j] < 10) os << "  " << GS.value[i][j] << "  |";
			else if (GS.value[i][j] < 100) os << "  " << GS.value[i][j] << " |";
			else if (GS.value[i][j] < 1000) os << " " << GS.value[i][j] << " |";
			else os << " " << GS.value[i][j] << "|";
		}
		os << "\n+-----+-----+-----+-----+\n";
	}

	return os;
}