#include <iostream>
#include <ctime>
#include <cmath>
#include <windows.h>

using namespace std;

struct Koordinat {
	short x, y;
};

struct Koordinat pieces[7][4] = {
		{{5, 0}, {5, 1}, {6, 0}, {6, 1}}, // O
		{{5, 0}, {5, 2}, {5, 1}, {5, 3}}, // I
		{{6, 0}, {7, 0}, {6, 1}, {5, 1}}, // S
		{{5, 0}, {6, 0}, {6, 1}, {7, 1}}, // Z
		{{5, 0}, {5, 2}, {5, 1}, {6, 2}}, // L
		{{6, 0}, {6, 2}, {6, 1}, {5, 2}}, // J
		{{4, 0}, {6, 0}, {5, 0}, {5, 1}}, // T
};

char stage[20][12] = {{'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '#'},
					  {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',  '#'},
				};

void move(short x, short y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {x, y});
}

int idx;

void getNextPieces(struct Koordinat *nextPiece) {
	idx = rand() % 7;
	//idx = 0;

	for(int i = 0; i < 4; ++i) {
		nextPiece[i] = pieces[idx][i];
	}
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 1;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void showcursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 7;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void draw() {
	for(int i = 0; i < 20; ++i) {
		for(int j = 0; j < 12; ++j) {
			if(stage[i][j] != 0) {
				std::cout << stage[i][j];
			} else {
				std::cout << ' ';
			}
		}

		std::cout << '\n';
	}
}

int main() {
	srand(time(0));

	int duration = 500;
	struct Koordinat centre = {5, 2};
	struct Koordinat temp[4], current_active_piece[4], prev_coord[4];
	hidecursor();
	getNextPieces(current_active_piece);
	GetAsyncKeyState(VK_UP);

	system("cls");
	draw();

	for(int n = 0; n < 2;) {
		for(int i = 0; i < 4; ++i) {
			prev_coord[i].x = current_active_piece[i].x;
			prev_coord[i].y = current_active_piece[i].y;

			if(stage[current_active_piece[i].y][current_active_piece[i].x] != 0) {
				std::cout << "GAME OVER\n";

				goto END;
			}
		}

		for(int i = 0; i < 4; ++i) {
			move(current_active_piece[i].x, current_active_piece[i].y);
			std::cout << '+';
		}

		bool flag = true;

		if(GetAsyncKeyState(VK_LEFT)) {
			for(int i = 0; i < 4; ++i) {
				if(stage[current_active_piece[i].y][current_active_piece[i].x - 1] != 0) {
					flag = false;
				}
			}

			if(flag) {
				for(int i = 0; i < 4; ++i) {
					current_active_piece[i].x -= 1;
				}
			}
		} else if(GetAsyncKeyState(VK_RIGHT)) {
			for(int i = 0; i < 4; ++i) {
				if(stage[current_active_piece[i].y][current_active_piece[i].x + 1] != 0) {
					flag = false;
					break;
				}
			}

			if(flag) {
				for(int i = 0; i < 4; ++i) {
					current_active_piece[i].x += 1;
				}
			}
		} else if(GetAsyncKeyState(VK_UP) and idx != 0){
			for(int i = 0; i < 4; ++i) {
				int x = current_active_piece[i].x - current_active_piece[2].x;
				int y = current_active_piece[i].y - current_active_piece[2].y;
				temp[i].x = -y + current_active_piece[2].x;
				temp[i].y = x + current_active_piece[2].y;

				if(temp[i].x >= 0 and temp[i].y >= 0 and stage[temp[i].y][temp[i].x] != 0) {
					flag = false;
					break;
				}
			}

			if(flag) {
				for(int i = 0; i < 4; ++i) {
					current_active_piece[i].x = temp[i].x;
					current_active_piece[i].y = temp[i].y;
				}
			}
		} else {
			for(int i = 0; i < 4; ++i) {
				temp[i].x = current_active_piece[i].x;
				temp[i].y = current_active_piece[i].y + 1;

				if(stage[temp[i].y][temp[i].x] != 0) {
					flag = false;
				}
			}

			if(flag) {
				for(int i = 0; i < 4; ++i) {
					current_active_piece[i].x = temp[i].x;
					current_active_piece[i].y = temp[i].y;
				}
			} else { //if reach the bottom of the stage
				for(int i = 0; i < 4; ++i) {
					stage[current_active_piece[i].y][current_active_piece[i].x] = 'O';
				}

				int count = 0;
				int y;

				for(int i = 18; i >= 0; --i) {
					flag = true;

					for(int j = 1; j < 10; ++j) {
						if(stage[i][j] == 0 or stage[i][j] != stage[i][j + 1]) {
							flag = false;
							break;
						}
					}

					if(flag){
						if(count == 0) {
							y = i;
						}

						++count;
					} 
				}

				if(count)
					for(int i = y; i >= count; --i) {
						for(int j = 1; j < 11; ++j) {
							stage[i][j] = stage[i - count][j];
						}
					}

				getNextPieces(current_active_piece);
				system("cls");
				draw();
				Sleep(duration);

				continue;
			}
		}

		Sleep(duration);

		//clear previous piece coordinate
		for(int i = 0; i < 4; ++i) {
			move(prev_coord[i].x, prev_coord[i].y);
			std::cout << ' ';
		}
	}

END:
	showcursor();

	return 0;
}
