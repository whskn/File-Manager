#include "Header.h"

static std::string copied_path;
static std::string copied_file_name;

std::string* local_files = new std::string[1000];
unsigned long long* size = new unsigned long long[1000]; // Size in Bytes
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int length = 0;
short cur = 0;

void clear_copy() {
	copied_path.clear();
	copied_file_name.clear();
}

void copy(std::string copy_path, std::string copy_file_name) { // pure
	if (copy_file_name != "..") {
		copied_path = copy_path;
		copied_file_name = copy_file_name;
	}
}

bool past(std::string copyto_path, bool a) { // pure
	return CopyFile((copied_path + copied_file_name).c_str(), (copyto_path + copied_file_name).c_str(), a);
}

bool move(std::string moveto_path, bool a) { // pure
	return MoveFileEx((copied_path + copied_file_name).c_str(), (moveto_path + copied_file_name).c_str(), a);
}

void del(std::string delete_path, std::string delete_file) {
	const char* const_delete_file = delete_path.append(delete_file).c_str();
	if (!RemoveDirectory(const_delete_file)) { // try to delete folder
		DeleteFile(const_delete_file); // try to delete file
	}
}

std::string this_file() {
	return local_files[cur];
}

int clr_local() {
	for (int i = 0; local_files[i][0] != NULL; i++) {
		local_files[i] = "\n";
		size[i] = NULL;
	}

	return 0;
}

int list(std::string path) {
	WIN32_FIND_DATA data;
	
	const char* const_path = path.append("*").c_str();
	HANDLE hFind = FindFirstFile(const_path, &data);
	int i;
	for(i = 0; FindNextFile(hFind, &data); i++){
		local_files[i] = data.cFileName;
		size[i] = data.nFileSizeLow;

		print(i);
	}

	cur = 0;
	cur_move(); // drow cursor
	length = i;

	return 0;
}

void print(int num) {
	if (local_files[num].length() > 20) { // cut file
		for (int i = 0; i < 20; i++) {
			std::cout << local_files[num][i];
		}
		std::cout << '~';
	}
	else {
		std::cout << local_files[num];
	}

	SetConsoleCursorPosition(hConsole, { 25, (short)num + 1 });
	if (size[num] > 0) { // rounding the size 
		if (size[num] >= 1000000000) {
			double value = (double)size[num] / 1073741824;
			value = int(value * 10);
			value = value / 10;
			std::cout << value << " GB" << std::endl;
		}
		else if (size[num] >= 1000000) {
			double value = (double)size[num] / 1048576;
			value = int(value * 10);
			value = value / 10;
			std::cout << value << " MB" << std::endl;
		}
		else if (size[num] >= 1000) {
			double value = (double)size[num] / 1024;
			value = int(value * 10);
			value = value / 10;
			std::cout << value << " KB" << std::endl;
		}
		else {
			std::cout << size[num] << " B" << std::endl;
		}
	}
	else {
		std::cout << '\n';
	}

	// in case you didnt get what this function do:
	// before: name - ThisIsMyFolderDontTouchIt, size - 1 073 741 824 B
	// after : name - ThisIsMyFolderDontTo~,	 size - 1 GB

}