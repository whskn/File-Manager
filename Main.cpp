#define NO_VARIABLES
#include "Header.h"
#include <conio.h>

static std::string path;

int key_hit(); // get key press
int up(); // go up to a directory
void down(std::string folder); // go down to a directory

int main() {
	setlocale(LC_ALL, "Russian");
	
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); // set cursor invisiable

	while (true) {
		while (true) {
			clear_copy();
			system("cls");
			std::cout << "\\help - get some help \nDrive: ";
			std::cin >> path;

			if (path == "\\help") {
				std::cout << "\nUP				- w" << std::endl;
				std::cout << "DOWN				- s" << std::endl;
				std::cout << "DELETE				- d (delete, not move to the bin! Doesn\'t delete unempty folders)" << std::endl;
				std::cout << "COPY				- c" << std::endl;
				std::cout << "PAST				- p (you should copy file before moving. doesn\'t past folders)" << std::endl;
				std::cout << "CREATE DIRECTORY		- n (if it doesn\'t, you do give a wrong name)" << std::endl;
				std::cout << "RENAME				- r (if it doesn\'t, you do give a wrong name)" << std::endl;
				std::cout << "MOVE				- m (you should copy file before moving)" << std::endl;
				system("pause");
			}
			else {
				path.append(":\\");
				break;
			}
		}

		while (true) {
			system("cls");
			std::cout << path << std::endl;

			list(path);
			if (key_hit()) {
				clr_local();
				break;
			}
			else {
				clr_local();
			}
		}
	}

	return 0;
}

int key_hit() {
	while (true) {
		if (_kbhit()) {
			switch (_getch()) {
			case ENTER:
				if (this_file() == "..") {
					return up();
				}
				else if (this_file() != "\n") {
					std::string execute_path = path + this_file();
					const char* const_path = execute_path.c_str();
					if ((FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(const_path)) == FILE_ATTRIBUTE_DIRECTORY) {
						down(this_file());
					}
					else {
						ShellExecute(NULL, "open", const_path, NULL, NULL, SW_NORMAL);
					}
				}
				return 0;

			case ESCAPE:
				return up();

			case UP:
				cur_move('u');
				break;

			case DOWN:
				cur_move('d');
				break;

			case DEL:
				del(path, this_file());
				return 0;

			case RENAME:
			{
				std::string new_name;

				do {
					system("cls");
					
					std::cout << "Directory name (\'.\' - back): ";
					std::cin >> new_name;
					if (new_name == ".") {
						return 0;
					}
				} while (!MoveFileEx((path + this_file()).c_str(), (path + new_name).c_str(), false));
					
				return 0;
			}

			case CREATE:
			{
				std::string new_dir;
				
				do {
					system("cls");
					std::cout << "Directory name (\'.\' - back): ";
					std::cin >> new_dir;
					if (new_dir == ".") {
						break;
					}
				} while (!CreateDirectory((path + new_dir).c_str(), NULL));

				return 0;
			}

			case COPY:
				copy(path, this_file());
				break;

			case MOVE:
				if (!move(path, true)) {
					system("cls");
					std::cout << "There is a file with the same name in this folder, \nreplace it? Y - yes/N - no" << std::endl;
					char a;
					std::cin >> a;
					if (a == 'Y' || a == 'y') {
						move(path, false);
					}
				}
				return 0;

			case PAST:
				if (!past(path, true)) {
					system("cls");
					std::cout << "There is a file with the same name in this folder, \nreplace it? Y - yes/N - no" << std::endl;
					char a;
					std::cin >> a;
					if (a == 'Y' || a == 'y') {
						past(path, false);
					}
				}
				return 0;
			}
		}
		Sleep(50);
	}

	return 0;
}

int up() {
	if (path.length() > 3) {
		path.pop_back();
		for (int i = path.length() - 1; path[i] != '\\'; i--) {
			path.pop_back();
		}
	}
	else {
		return 1;
	}
	return 0;
}

void down(std::string folder) {
	path.append(this_file());
	path.append("\\");
}