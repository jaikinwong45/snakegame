#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;
const int width = 15;
const int height = 15;
bool gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
// Prototype functions 
void Setup();
void Drawborder();
void Input();
void Logic();
void Displaymenu();
void Rules();

int main() {
	int choice, allg;
	Displaymenu();
	cout << "Enter choice: ";
	cin >> choice;
	while (choice < 1 || choice > 2)
	{
		cout << "Error";
	}
	switch (choice)
	{
	case 1:
		Rules();
		cin >> allg;
		if (allg == 1)
		{
			Setup();
			while (!gameOver)
			{
				Drawborder();
				Input();
				Logic();
				Sleep(100);  // Sleep for 1000 milliseconds
			}
		}
		else
			break;
	case 2:
		break;
	}

	return 0;
}


void Drawborder()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)

		cout << "-";  // Draws top border
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "|"; // draws left border
			if (i == y && j == x)
				cout << "O";   // head uses capital O
			else if (i == fruitY && j == fruitX)
				cout << "#";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o"; // body uses lower case o
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "|"; //draws right border
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "-"; // draws bottom border
	cout << endl;
	cout << "Score:" << score << endl;
}

void Displaymenu()
{
	cout << "Enter 1 to play " << endl;
	cout << "Enter 2 to cancel " << endl;

}
void Rules()
{
	cout << "Rules and Instructions" << endl;
	cout << "To move the snake the user must use the WASD keys." << endl;
	cout << "The user's score wll increase by one the fruit is captured by the snake." << endl;
	cout << "If the snake makes contact with the wall the snake with enter through the opposite side" << endl;
	cout << "The game will end when if the user's head of the snake makes contact with the tail" << endl;
	cout << "Enter 1 to continue: " << endl;


}
void Setup()
{
	srand(static_cast<unsigned>(time(0)));  // Seed for randomization
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}



void Input()
{
	if (_kbhit())
	{
		switch (_getch()) {
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
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prevXX, prevYY;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prevXX = tailX[i];
		prevYY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prevXX;
		prevY = prevYY;
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
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x >= width) x = 0;
	else if (x < 0) x = width - 1;
	if (y >= height) y = 0;
	else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 1;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}