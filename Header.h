#pragma once

#include <iostream>
#include <Windows.h> // WINAPI

// move
#define UP		'w'
#define DOWN	's'
#define DEL		'd'
#define COPY	'c'
#define PAST	'p'
#define MOVE    'm'
#define CREATE  'n'
#define RENAME  'r'
#define ENTER	13 // "ENTER" button
#define ESCAPE	27 // "ESC" button

// other
#define CUR_COLOR 248

#ifndef NO_VARIABLES
#define NO_VARIABLES
extern std::string* local_files;	// buffer of files in the current directory
extern unsigned long long* size;	// Size in Bytes
extern HANDLE hConsole;				// handle of the console
extern int length;					// length of the local files
extern short cur;					// cursor position
#endif

bool past(std::string copyto_path, bool a); // past file
bool move(std::string moveto_path, bool a); // move file
int list(std::string path); // list files in a directory
void del(std::string delete_path, std::string delete_file); // delete file
std::string this_file(); // get name of file that cursor on
void print(int num); // cut (if length of the file longer than 20 symbols) & print name and round and print size of the file
void copy(std::string copy_file, std::string copy_file_name); // copy file 
void cur_move(char direction = '0'); // move cursol
int clr_local(); // clear local files buffer
void clear_copy(); // clear copy buffer