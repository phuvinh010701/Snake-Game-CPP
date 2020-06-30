#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>

#define size 16

using namespace std;

int n = 30, m = 15;
int dir, num = 3;


struct SNAKE {
	int x, y;
}s[100];

struct FRUIT {
	int x, y;
}f;


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

inline void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);

}


bool check() {

	for (int i = 1; i < num; ++i) {
		if (s[0].x == s[i].x && s[0].y == s[i].y)
			return false;
	}

	if (s[0].x >= n - 1 || s[0].x < 0 || s[0].y >= m - 1 || s[0].y < 0) {
		return false;
	}

}



void Draw() {

	for (int i = 0; i <= m; ++i) {
		for (int j = 0; j <= n; ++j) {
			if (i == 0 || j == 0 || i == m || j == n) {
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 1; i <= num; i++) {
		gotoXY(s[i].x + 1, s[i].y + 1);
		printf("X");
	}

	gotoXY(f.x, f.y);
	printf("O");

}

void tick() {

	for (int i = num; i > 0; --i) {
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 0) {
		s[0].y += 1;
	}
	else if (dir == 1) {
		s[0].x -= 1;
	}
	else if (dir == 2) {
		s[0].x += 1;
	}
	else if (dir == 3) {
		s[0].y -= 1;
	}


	if (s[0].x == f.x - 1 && s[0].y == f.y - 1) {

		num++;
		srand(time(0));
		f.x = rand() % (n - 1) + 1;
		f.y = rand() % (m - 1) + 1;

	}

}

int main() {


	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	f.x = rand() % (n - 1) + 1;
	f.y = rand() % (m - 1) + 1;

	char t;

	while (1) {

		if (_kbhit()) {

			t = _getch();
			if ((t == 77 && dir == 1) || (t == 75 && dir == 2) || (t == 72 && dir == 0) || (t == 80 && dir == 3)) {
				continue;
			}
			else {

				if (t == 75) dir = 1;
				else if (t == 77) dir = 2;
				else if (t == 72) dir = 3;
				else if (t == 80) dir = 0;

			}


		}

		tick();
		Draw();
		if (check() == false) {

			Sleep(300);
			system("cls");
			cout << "You lose. Your score: " << num - 3;
			break;

		}

		Sleep(100);
		system("cls");

	}

	_getch();
}