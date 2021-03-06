// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <stack>
#include <fstream>
using namespace std;

#define SIZE 11

struct cell {
	bool visited;
	bool top_wall;
	bool bot_wall;
	bool left_wall;
	bool right_wall;
	char display;
};

void init(cell level[][SIZE]);
void clear();
void redraw(cell level[][SIZE]);
void genMaze(cell level[][SIZE], int &posX, int &posY, int &goalX, int &goalY);
void saveMaze();

int main() {
	cell level[SIZE][SIZE];
	int posX = 0;
	int posY = 0;
	int goalX = 0;
	int goalY = 0;
	bool endMaze = false;
	
	while (!endMaze) {
		init(level);
		redraw(level);
		genMaze(level, posX, posY,goalX, goalY);

		char input;
		cout << "Generate a Maze? Y/N: ";
		cin >> input;

		if ((input != 'n') && (input != 'N') && (input != 'y') && (input != 'Y')) {
			cout << "try again";
		}
		else if ((input == 'n') || (input == 'N')) {
			endMaze = true;
			cout << "GoodBye!" << endl;
		}
	}
	_getch();
	return 0;
}

void init(cell level[][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			level[i][j].display = '*';
			level[i][j].visited = false;
			level[i][j].top_wall = true;
			level[i][j].bot_wall = true;
			level[i][j].right_wall = true;
			level[i][j].left_wall = true;
		}
	}

	for (int i = 0; i < SIZE - 1; i++) {
		for (int j = 0; j < SIZE - 1; j++) {
			level[1][j].top_wall = false;
			level[SIZE - 2][j].bot_wall = false;
			level[i][1].left_wall = false;
			level[i][SIZE - 2].right_wall = false;
		}
	}

}

void clear() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);

}

void redraw(cell level[][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		cout << endl;
		for (int j = 0; j < SIZE; j++) {
			cout << " " << level[i][j].display;
		}
	}
}

void genMaze(cell level[][SIZE], int &posX, int &posY, int &goalX, int &goalY) {
	srand((unsigned)time(NULL));
	int random = 0;
	int randomX = ((2 * rand()) + 1) % (SIZE - 1);
	int randomY = ((2 * rand()) + 1) % (SIZE - 1);
	posX = randomX;
	posY = randomY;
	int visitedCells = 1;
	int totalCells = ((SIZE - 1) / 2) * ((SIZE - 1) / 2);
	int percent = 0;
	stack<int> backTrackX, backTrackY; 

	level[randomY][randomX].display = 'S';
	level[randomY][randomX].visited = true;

	//yeet and yote
	while (visitedCells < totalCells) {
		if (((level[randomY - 2][randomX].visited == false) && (level[randomY][randomX].top_wall == true && level[randomY - 2][randomX].bot_wall == true))
			|| ((level[randomY + 2][randomX].visited == false) && (level[randomY][randomX].bot_wall == true && level[randomY + 2][randomX].top_wall == true))
			|| ((level[randomY][randomX - 2].visited == false) && (level[randomY][randomX].left_wall == true && level[randomY][randomX - 2].right_wall == true))
			|| ((level[randomY][randomX + 2].visited == false) && (level[randomY][randomX].right_wall == true && level[randomY][randomX + 2].left_wall == true))) 
		{

			random = (rand() % 4) + 1;

			//Going up
			if ((random == 1) && (randomY > 1)) {
				if (level[randomY - 2][randomX].visited == false) {
					level[randomY - 1][randomX].display = ' ';
					level[randomY - 1][randomX].visited = true;
					level[randomY][randomX].top_wall = false;

					backTrackX.push(randomX);
					backTrackX.push(randomY);

					randomY -= 2;

					level[randomY][randomX].visited = true;
					level[randomY][randomX].display = ' ';
					level[randomY][randomX].bot_wall = false;
					visitedCells++;
				}
				else {
					continue;
				}
			}

			//Going down
			else if ((random == 2) && (randomY < SIZE - 2)) {
				if (level[randomY + 2][randomX].visited == false) {
					level[randomY + 1][randomX].display = ' ';
					level[randomY + 1][randomX].visited = true;
					level[randomY][randomX].bot_wall = false;

					backTrackX.push(randomX);
					backTrackY.push(randomY);

					randomY += 2;

					level[randomY][randomX].visited = true;
					level[randomY][randomX].display = ' ';
					level[randomY][randomX].top_wall = false;
					visitedCells++;

				}
				else {
					continue;
				}

			}

			//Going left 
			else if ((random == 3) && (randomX > 1)) {
				if (level[randomY][randomX - 2].visited == false) {
					level[randomY][randomX - 1].display = ' ';
					level[randomY][randomX - 1].visited = true;
					level[randomY][randomX].left_wall = false;

					backTrackX.push(randomX);
					backTrackY.push(randomY);

					randomX -= 2;

					level[randomY][randomX].visited = true;
					level[randomY][randomX].display = ' ';
					level[randomY][randomX].right_wall = false;
					visitedCells++;
				}
				else {
					continue;
				}
			}

			//Going right
			else if ((random == 4) && (randomX < SIZE - 2)) {
				if (level[randomY][randomX + 2].visited == false) {
					level[randomY][randomX + 1].display = ' ';
					level[randomY][randomX + 1].visited = true;
					level[randomY][randomX].right_wall = false;

					backTrackX.push(randomX);
					backTrackY.push(randomY);

					randomX += 2;

					level[randomY][randomX].visited = true;
					level[randomY][randomX].display = ' ';
					level[randomY][randomX].left_wall = false;
					visitedCells++;
				}
				else {
					continue; 
				}
			}
			percent = (visitedCells * 100 / totalCells * 100) / 100;
			cout << endl << "loading maze..." << percent << "%" << endl;

		}
		else {
			randomX = backTrackX.top();
			backTrackX.pop();
			randomY = backTrackY.top();
			backTrackY.pop();
		}
		clear();
		redraw(level);

	}
	goalX = randomX;
	goalY = randomY;
	level[goalY][goalX].display = 'E';
	system("cls");
	clear();
	redraw(level);
	cout << endl << "\a\t Complete" << endl;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
