#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <ctime>
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

// hinh dang cua mot not ran
#define DOT_RAN 254

//hinh dang cua fruit
#define FRUIT '0'
// chieu dai max
#define MAX 100

// toa do cac buc tuong
#define TREN 0
#define DUOI 20
#define TRAI 0
#define PHAI 60
// so do ban dau 
#define DEFAULT_DOT 2
struct TOADO {
	int x, y;
	int color;
};

TOADO ran[MAX];
int soDot = 2;

int inputKey();							// lay phim tu keyboard
void clrscr();							// xoa man hinh
void gotoXY(int x, int y);				// di chuyen den toa do XY
int whereX();							// vi tri X
int whereY();							// vi tri y
void noCursorType();					// xoa con tro nhap nhay
void setTextColor(int color);			// chinh mau text
void init_snake();						// khoi tao ran
void draw_snake(TOADO last_point);		// ve ran
TOADO move(int huong);					// di chuyen ran
void batsk(int& huong);					// bat su kien tu ban phim
void draw_wall();						// ve tuong
bool check_game_over();					// kiem tra dung game
int game_over();						// xu li game over
TOADO random_fruit();					// tao moi ngau nhien
bool check_snake_eat(TOADO fruit);		// kiem tra ran an moi
void snake_eat(TOADO& fruit, int& time);// xu li khi ran an duoc moi
void display_menu();					// hien thi bang menu
void select_difficulty(int& time);		// chon do kho


int main() {
	int k;
	do {
		setTextColor(15);
		display_menu();

		int time;

		select_difficulty(time);

		clrscr();

		setTextColor(15);

		init_snake();
		noCursorType();
		draw_wall();

		int huong = KEY_RIGHT;
		TOADO fruit = random_fruit();

		// game loop
		while (true) {

			TOADO last_point = move(huong);
			batsk(huong);
			draw_snake(last_point);
			if (check_game_over()) {
				break;
			}
			if (check_snake_eat(fruit)) {
				snake_eat(fruit, time);
			}
			Sleep(time);
		}
		k = game_over();

	} while (k != '0');

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
	ran[0].x = ran[0].y = 1;
	ran[1].x = ran[1].y = 2;
	ran[0].color = 1;
	ran[1].color = 2;
}

void draw_snake(TOADO last_point) {
	srand(time(0));
	for (int i = 0; i < soDot; ++i) {
		setTextColor(ran[i].color);
		gotoXY(ran[i].x, ran[i].y);
		cout << (char)254;
	}

	gotoXY(last_point.x, last_point.y);
	cout << " ";
}

TOADO move(int huong) {
	TOADO last_point = ran[soDot - 1];
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
	return last_point;
}

void batsk(int& huong) {
	int key = inputKey();
	if (key == 1072 && huong != 1080) huong = KEY_UP;
	else if (key == 1080 && huong != 1072) huong = KEY_DOWN;
	else if (key == 1075 && huong != 1077) huong = KEY_LEFT;
	else if (key == 1077 && huong != 1075) huong = KEY_RIGHT;
	else {
		return;
	}
}

void draw_wall() {
	for (int x = TRAI; x <= PHAI; ++x) {
		setTextColor(12);
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
		if (ran[0].x == ran[i].x && ran[0].y == ran[i].y) return true;
	}
	return false;
}

int game_over() {
	clrscr();
	setTextColor(12);
	cout << "Your score: " << soDot - DEFAULT_DOT << "\n";
	soDot = DEFAULT_DOT;									// dat lai chieu dai cua ran
	setTextColor(10);
	cout << "Press 1 to try again." << "\n" << "Press 0 to exit." << "\n";
	int k;
	do {
		k = _getch();
	} while (k != '1' && k != '0');
	clrscr();
	return k;
}

TOADO random_fruit() {
	srand(time(0));
	TOADO temp;
	temp.x = TRAI + 1 + rand() % (PHAI - TRAI - 1);			// random tu (TRAI, PHAI)
	temp.y = TREN + 1 + rand() % (DUOI - TREN - 1);
	temp.color = rand() % 15 + 1;
	setTextColor(temp.color);
	gotoXY(temp.x, temp.y);
	cout << (char)FRUIT;
	return temp;
}

bool check_snake_eat(TOADO fruit) {
	if (ran[0].x == fruit.x && ran[0].y == fruit.y) {
		ran[0] = fruit;
		return true;
	}
	return false;
}

void snake_eat(TOADO& fruit, int& time) {
	fruit = random_fruit();
	soDot++;
	if (time > 75) {					// gioi han de ran khong chay qua nhanh
		time -= 5;						// tang toc do cua ran
	}
}


void display_menu() {
	cout << "\n\n     MINI GAME: \n\n";
	cout << "         .*****.   ***       **         ***         **   '*'   *.*.*.*.*.   " << endl;
	cout << "        **'    '*  **'*      **        *' '*        **  '*'     **''''''*   " << endl;
	cout << "        **      '  ** *'     **       *'   '*       ** '*'      **          " << endl;
	cout << "         **        **  '*    **      '*     *'      **'*'       **.....     " << endl;
	cout << "           '**.    **   *.   **     .*'.....'*.     ***'        **.*.*.     " << endl;
	cout << "              '*   **    *'  **     *.*.*.*.*.*     **'*'       **          " << endl;
	cout << "        .      **  **     '* **    *'         '*    ** '*'      **          " << endl;
	cout << "        **.   .**  **      *'**   '*           *'   **  '*'     **......*   " << endl;
	cout << "         '*****'   **       ***  '*'           '*'  **   '*'.  *'*'*'*'*'   " << endl;

	cout << "\nChon do kho:" << "\n";
	cout << "1. Rat de" << "\n";
	cout << "2. De" << "\n";
	cout << "3. Trung binh" << "\n";
	cout << "4. Kho" << "\n";
	cout << "5. Cuc kho" << "\n";
}

void select_difficulty(int& time) {
	int dokho;
	do {
		dokho = _getch();
		switch (dokho) {
		case '1':
			time = 500;				// rat de
			break;
		case '2':
			time = 400;				// de
			break;
		case '3':
			time = 300;				// trung binh
			break;
		case '4':
			time = 150;				// kho
			break;
		case '5':
			time = 55;				// rat kho
			break;
		}
	} while (dokho < '1' || dokho > '5');
}