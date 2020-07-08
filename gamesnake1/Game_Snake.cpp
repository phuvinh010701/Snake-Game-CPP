#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>

using namespace std;

// color
#define BLACK_COLOR			0
#define DARK_BLUE_COLOR		1
#define DARK_GREEN_COLOR	2
#define DARK_CYAN_COLOR		3
#define DARK_RED_COLOR		4
#define DARK_PINK_COLOR		5
#define DARK_YELLOW_COLOR	6
#define DARK_WHITE_COLOR	7
#define GREY_COLOR			8
#define BLUE_COLOR			9
#define GREEN_COLOR			10
#define CYAN_COLOR			11
#define RED_COLOR			12
#define PINK_COLOR			13
#define YELLOW_COLOR		14
#define WHITE_COLOR			15

// get key
#define KEY_UP		1072
#define KEY_DOWN	1080
#define KEY_LEFT	1075
#define KEY_RIGHT	1077
#define KEY_NONE	-1

// chieu dai ran
#define DOT_RAN 254

// chieu dai max
#define MAX 100

// toa do cac buc tuong
#define TREN 0
#define DUOI 20
#define TRAI 0
#define PHAI 60

struct TOADO {
	int x, y;
};

TOADO ran[MAX];
int soDot = 3;

int inputKey();
void clrscr(); // xoa man hinh
void gotoXY(int x, int y); // di chuyen den toa do XY
int whereX(); // vi tri X
int whereY(); // vi tri y
void noCursorType(); // xoa con tro nhap nhay
void setTextColor(int color); // chinh mau text
void init_snake(); // khoi tao ran
void draw_snake(); // ve ran
void move(int huong); // di chuyen ran
void batsk(int& huong); // bat su kien tu ban phim
void draw_wall(); // ve tuong
bool check_game_over(); // kiem tra dung game

int main() {
	init_snake();

	int huong = KEY_RIGHT;
	noCursorType();
	// game loop
	while (true) {
		clrscr();
		draw_wall();
		move(huong);
		batsk(huong);
		draw_snake();
		if (check_game_over()) {
			break;
		}
		Sleep(100);
	}

}


int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}

	return KEY_NONE;
}

void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

void noCursorType()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = FALSE;
	info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void setTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void init_snake() {
	ran[0].x = 4;
	ran[1].x = 5;
	ran[2].x = 6;
	ran[0].y = ran[1].y = ran[2].y = 1;
}

void draw_snake() {
	for (int i = 0; i < soDot; ++i) {
		gotoXY(ran[i].x, ran[i].y);
		cout << char(DOT_RAN);
	}
}
void move(int huong) {

	for (int i = soDot - 1; i >= 1; --i) {
		ran[i] = ran[i - 1];
	}
	switch (huong) {
	case KEY_UP:
		ran[0].y--;
		break;
	case KEY_DOWN:
		ran[0].y++;
		break;
	case KEY_LEFT:
		ran[0].x--;
		break;
	case KEY_RIGHT:
		ran[0].x++;
		break;
	}
}

void batsk(int& huong) {
	int key = inputKey();
	if (key == 1072) huong = KEY_UP;
	else if (key == 1080) huong = KEY_DOWN;
	else if (key == 1075) huong = KEY_LEFT;
	else if (key == 1077) huong = KEY_RIGHT;
	else {
		return;
	}
}

void draw_wall() {
	for (int x = TRAI; x <= PHAI; ++x) {
		gotoXY(x, TREN);
		cout << (char)223;
		gotoXY(x, DUOI);
		cout << (char)220;
	}
	for (int y = TREN; y <= DUOI; ++y) {
		gotoXY(TRAI, y);
		cout << (char)222;
		gotoXY(PHAI, y);
		cout << (char)221;
	}
}

bool check_game_over() {
	if (ran[0].y == TREN || ran[0].y == DUOI || ran[0].x == TRAI || ran[0].x == PHAI) {
		return true;
	}
	for (int i = 1; i < soDot; ++i) {
		if (ran[0].x == ran[i].x && ran[0].y == ran[i].y) return false;
	}
	return false;
}
