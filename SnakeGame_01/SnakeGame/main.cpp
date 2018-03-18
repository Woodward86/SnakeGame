#include <iostream>
#include <conio.h>
#include <windows.h>

enum eDirection
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

bool bGameOver;

// Map dimensions
const int Width = 40;
const int Height = 20;
// Head location
int x;
int y;
// Fruit location
int FruitX;
int FruitY;
// Score 
int Score;

int TailX[100];
int TailY[100];
int nTail;
 
eDirection dir;

void Setup()
{
	bGameOver = false;
	dir = STOP;
	x = Width / 2;
	y = Height / 2;
	FruitX = rand() % Width;
	FruitY = rand() % Height;
	Score = 0;
}


void Draw()
{
	system("cls"); // clears the system console window

	for (int i = 0; i < Width + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
	

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (j == 0)
			{
				std::cout << "#";
			}
			if (i == y && j == x)
			{
				std::cout << "O";
			}
			else if (i == FruitY && j == FruitX)
			{
				std::cout << "*";
			}
			else
			{
				bool bPrint = false;
				for (int k = 0; k < nTail; k++)
				{
					if (TailX[k] == j && TailY[k] == i)
					{
						std::cout << "o";
						bPrint = true;
					}
				}
				if (!bPrint)
				{
					std::cout << " ";
				}
			}
			if (j == Width - 1)
			{
				std::cout << "#";
			}
		}
		std::cout << std::endl;
	}
	
	for (int i = 0; i < Width + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
	std::cout << "Score: " << Score << std::endl;
}


void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			bGameOver = true;
			break;
		}
	}
}


void Logic()
{
	int PrevX = TailX[0];
	int PrevY = TailY[0];
	int Prev2X;
	int Prev2Y;
	TailX[0] = x;
	TailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		Prev2X = TailX[i];
		Prev2Y = TailY[i];
		TailX[i] = PrevX;
		TailY[i] = PrevY;
		PrevX = Prev2X;
		PrevY = Prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		Sleep(5); // slows movement
		break;
	case DOWN:
		y++;
		Sleep(5); // slows movement
		break;
	default:
		break;
	}
	if (x > Width || x < 0 || y > Height || y < 0)
	{
		bGameOver = true;
	}
	for (int i = 0; i < nTail; i++)
	{
		if (TailX[i] == x && TailY[i] == y)
		{
			bGameOver = true;
		}
	}
	if (x == FruitX && y == FruitY)
	{
		Score += 10;
		FruitX = rand() % Width;
		FruitY = rand() % Height;
		nTail++;
	}
}


int main()
{
	Setup();
	while (!bGameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(10); // slows entire game
	}
	return 0;
}