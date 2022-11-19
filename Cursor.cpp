#include "Header.h"

void cur_move(char direction) {
	SetConsoleCursorPosition(hConsole, { 0, cur + 1 }); // "paint" last cursor position
	print(cur);

	if (direction == 'u') { // check direction
		if (cur == 0) cur = length - 1;
		else cur--;
	}
	else if (direction == 'd') {
		if (cur == length - 1) cur = 0;
		else cur++;
	}

	SetConsoleCursorPosition(hConsole, { 0, cur + 1 }); // set new curor position
	SetConsoleTextAttribute(hConsole, CUR_COLOR); // "paint" current cursor position
	print(cur);
	SetConsoleTextAttribute(hConsole, 7);
}