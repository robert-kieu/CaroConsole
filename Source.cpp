#include<iostream>
#include<CoreWindow.h>
#include<conio.h>
#include<Windows.h>
using namespace std;
//================CONST======================
#define BOARD_SIZE 12
#define LEFT 3
#define TOP 1
struct _POINT { int x, y, c; };
_POINT _A[BOARD_SIZE][BOARD_SIZE];
bool _TURN;
int _COMMAND;
int _X, _Y;
//=============END_DEFINE============

//view:

void fixconsolewindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void color(int x)
{
	HANDLE setcolor;
	setcolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(setcolor, x);
}

void headofgame(int n)
{
	while (n > 0)
	{
		color(rand() % 10 + 1);
		gotoXY(11, 5);  cout << " ________  ______   ______         ________  ______    ______         ________  ______   ________ ";
		gotoXY(11, 6);  cout << "/        |/      | /      |       /        |/      |  /      |       /        |/      | /        |";
		gotoXY(11, 7);  cout << "$$$$$$$$/ $$$$$$/ /$$$$$$  |      $$$$$$$$//$$$$$$  |/$$$$$$  |      $$$$$$$$//$$$$$$  |$$$$$$$$/ ";
		gotoXY(11, 8);  cout << "   $$ |     $$ |  $$ |  $$/          $$ |  $$ |__$$ |$$ |  $$/          $$ |  $$ |  $$ |$$ |__    ";
		gotoXY(11, 9);  cout << "   $$ |     $$ |  $$ |               $$ |  $$    $$ |$$ |               $$ |  $$ |  $$ |$$    |   ";
		gotoXY(11, 10); cout << "   $$ |     $$ |  $$ |   __          $$ |  $$$$$$$$ |$$ |   __          $$ |  $$ |  $$ |$$$$$/    ";
		gotoXY(11, 11); cout << "   $$ |    _$$ |_ $$ |__/  |         $$ |  $$ |  $$ |$$ |__/  |         $$ |  $$ |__$$ |$$ |_____ ";
		gotoXY(11, 12); cout << "   $$ |   / $$   |$$    $$/          $$ |  $$ |  $$ |$$    $$/          $$ |  $$    $$/ $$       |";
		gotoXY(11, 13); cout << "   $$/    $$$$$$/  $$$$$$/           $$/   $$/   $$/  $$$$$$/           $$/    $$$$$$/  $$$$$$$$/ ";
		Sleep(100);
		n--;
	}
}

void resetdata()
{
	for (int i = 0; i <= BOARD_SIZE; i++)
		for (int j = 0; j <= BOARD_SIZE; j++)
		{
			_A[i][j].x = 4 * j + LEFT + 2;
			_A[i][j].y = 2 * i + TOP + 1;
			_A[i][j].c = 0;
		}
	_TURN = true; _COMMAND = -1;
	_X = _A[0][0].x; _Y = _A[0][0].y;
}
void drawcrossboard()
{
	for (int i = 14 + (2 * (BOARD_SIZE + BOARD_SIZE) + 3); i <= 2*(2 * (BOARD_SIZE + BOARD_SIZE) + 3) + 14; i++)
	{
		gotoXY(i, 0); cout << "####";
	}
	for (int i = 14 + (2 * (BOARD_SIZE + BOARD_SIZE) + 3); i <= 2*(2 * (BOARD_SIZE + BOARD_SIZE) + 3) + 14; i++)
	{
		gotoXY(i, 26); cout << "####";
	}
	for (int i = 1; i <= BOARD_SIZE * 2 + 1; i++)
	{
		gotoXY(14 + (2 * (BOARD_SIZE + BOARD_SIZE) + 3), i); cout << "##";
	}
	for (int i = 1; i <= BOARD_SIZE * 2 + 1; i++)
	{
		gotoXY(2 * (2 * (BOARD_SIZE + BOARD_SIZE) + 3) + 16, i); cout << "##";
	}
}
void Xwin()
{
	gotoXY(26, 30); cout << "#####  #        ##   #   # ###### #####     #    #    #    # # #    #";
	gotoXY(26, 31); cout << "#    # #       #  #   # #  #      #    #     #  #     #    # # ##   #";
	gotoXY(26, 32); cout << "#    # #      #    #   #   #####  #    #      ##      #    # # # #  #";
	gotoXY(26, 33); cout << "#####  #      ######   #   #      #####       ##      # ## # # #  # #";
	gotoXY(26, 34); cout << "#      #      #    #   #   #      #   #      #  #     ##  ## # #   ##";
	gotoXY(26, 35); cout << "#      ###### #    #   #   ###### #    #    #    #    #    # # #    #";
}
void Owin()
{
	gotoXY(26, 30); cout << "#####  #        ##   #   # ###### #####      ####     #    # # #    #";
	gotoXY(26, 31); cout << "#    # #       #  #   # #  #      #    #    #    #    #    # # ##   #";
	gotoXY(26, 32); cout << "#    # #      #    #   #   #####  #    #    #    #    #    # # # #  #";
	gotoXY(26, 33); cout << "#####  #      ######   #   #      #####     #    #    # ## # # #  # #";
	gotoXY(26, 34); cout << "#      #      #    #   #   #      #   #     #    #    ##  ## # #   ##";
	gotoXY(26, 35); cout << "#      ###### #    #   #   ###### #    #     ####     #    # # #    #";
}
void xodraw()
{
	gotoXY(45, 30); cout << "######  ######     #    #     #";
	gotoXY(45, 31); cout << "#     # #     #   # #   #  #  #";
	gotoXY(45, 32); cout << "#     # #     #  #   #  #  #  #";
	gotoXY(45, 33); cout << "#     # ######  #     # #  #  #";
	gotoXY(45, 34); cout << "#     # #   #   ####### #  #  #";
	gotoXY(45, 35); cout << "#     # #    #  #     # #  #  #";
	gotoXY(45, 36); cout << "######  #     # #     #  ## ## ";
}
void drawboard(int bsize)
{
	for (int i = 1; i <= BOARD_SIZE * 2 + 1; i++)
	{
		gotoXY(0, i); cout << "##";
	}
	for (int i = 1; i <= BOARD_SIZE * 2 + 1; i++)
	{
		gotoXY(53, i); cout << "##";
	}
	for (int i = 0; i <= 2 * (BOARD_SIZE + BOARD_SIZE) + 3; i++)
	{
		gotoXY(i, 0); cout << "####";
	}
	for (int i = 0; i <= 2 * (BOARD_SIZE + BOARD_SIZE) + 3; i++)
	{
		gotoXY(i, 26); cout << "####";
	}
	drawcrossboard();
	for (int i = 0; i <= bsize; i++)
		for (int j = 0; j <= bsize; j++)
		{
			gotoXY(LEFT + 4 * i, TOP + 2 * j);
			printf("+");
		}
	gotoXY(5, 2);
}

int processfinishing(int pwhowin)
{
	gotoXY(0, 27);
	switch (pwhowin)
	{
	case -1:
	{
		Xwin();
		break;
	}
	case 1: 
	{
		Owin();
		break;
	}
	case 0:
	{
		xodraw();
		break;
	}
	case 2:
	{
		_TURN = !_TURN;
		break;
	}
	}
	gotoXY(_X, _Y);
	return pwhowin;
}

char askcontinue()
{
	gotoXY(45, 39); color(10);
	printf("Press Y to continue N to stop : ");
	return toupper(_getch());
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void turnX()
{
	gotoXY(75, 5);
	if (_TURN == true) cout << " X TURN ";
}
void turnO()
{
	gotoXY(75, 5);
	if (_TURN != true) cout << " O TURN ";
}
//========End_View============================================

//Function_Model:
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**+*+*+*+*+*+**+

bool draw()
{
	int count = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].c == -1 || _A[i][j].c == 1) count++;
		}
		if (count == 144) return true;
	}
}
bool check_row()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((_A[i][j].c == -1 || _A[i][j].c == 1) && _A[i][j].c == _A[i][j + 1].c && _A[i][j].c == _A[i][j + 2].c && _A[i][j].c == _A[i][j + 3].c && _A[i][j].c == _A[i][j + 4].c) return true;
			else continue;
		}
}
bool check_colum()
{
	for (int j = 0; j < BOARD_SIZE; j++)
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			if ((_A[i][j].c == -1 || _A[i][j].c == 1) && _A[i][j].c == _A[i + 1][j].c && _A[i][j].c == _A[i + 2][j].c && _A[i][j].c == _A[i + 3][j].c && _A[i][j].c == _A[i + 4][j].c) return true;
			else continue;
		}
}
bool maincross()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((_A[i][j].c == -1 || _A[i][j].c == 1) && _A[i][j].c == _A[i - 1][j + 1].c && _A[i][j].c == _A[i - 2][j + 2].c && _A[i][j].c == _A[i - 3][j + 3].c && _A[i][j].c == _A[i - 4][j + 4].c) return true;
			else continue;
		}
}
bool appendcross()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((_A[i][j].c == -1 || _A[i][j].c == 1) && _A[i][j].c == _A[i + 1][j + 1].c && _A[i][j].c == _A[i + 2][j + 2].c && _A[i][j].c == _A[i + 3][j + 3].c && _A[i][j].c == _A[i + 4][j + 4].c) return true;
			else continue;
		}
}
bool winer()
{
	if (check_row() == true || check_colum() == true || maincross() == true || appendcross() == true) return true;
}
//*+*+*+*+*+**+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**+*+*
int testboard()
{
	if (draw() == true) return 0;
	else if (winer() == true) return (_TURN == true ? -1 : 1);
	else return 2;
}

int checkboard(int pX, int pY)
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0)
			{
				if (_TURN == true) _A[i][j].c = -1;
				else _A[i][j].c = 1;
				return _A[i][j].c;
			}
		}
	return 0;
}

//========End_Model===============================

//Function_Control:
void startgame()
{
	system("cls");
	resetdata();
	drawboard(BOARD_SIZE);
}

void gabagecollect() {}

void exitgame()
{
	system("cls");
	gabagecollect();
	//Save game
}

void moveright()
{
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)
	{
		_X += 4; gotoXY(_X, _Y);
	}
}

void moveleft()
{
	if (_X > _A[0][0].x)
	{
		_X -= 4;
		gotoXY(_X, _Y);
	}
}

void movedown()
{
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
	{
		_Y += 2;
		gotoXY(_X, _Y);
	}
}

void moveup()
{
	if (_Y > _A[0][0].y)
	{
		_Y -= 2;
		gotoXY(_X, _Y);
	}
}

void moveingame()
{
	bool validEnter = true;
	while (1)
	{
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27) { exitgame(); return; }
		else
		{
			if (_COMMAND == 'A' || _COMMAND == 75) moveleft();
			else if (_COMMAND == 'D' || _COMMAND == 77) moveright();
			else if (_COMMAND == 'S' || _COMMAND == 80) movedown();
			else if (_COMMAND == 'W' || _COMMAND == 72) moveup();
			else if (_COMMAND == 13 || _COMMAND == 32)
			{
				switch (checkboard(_X, _Y))
				{
				case -1:
					color(12); printf("X"); turnO(); break;
				case 1:
					color(11); printf("O"); break;
				case 0: validEnter = false;
				}
				if (validEnter == true)
				{
					switch (processfinishing(testboard()))
					{
					case -1: case 1: case 0:
						if (askcontinue() == 89 || askcontinue() == 121)
						{
							color(6);
							startgame();
						}
						else exitgame();
					}
				}
				validEnter = true;
			}
		}
	}
}
//========End_Control=======================
void main()
{
	headofgame(30);
	_getch();
	fixconsolewindow();
	startgame();
	moveingame();
}