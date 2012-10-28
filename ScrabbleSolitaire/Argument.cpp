// Argument.cpp
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Contains functions related to the program argument help usage message

#include "stdafx.h"
#include "Argument.h"
#include "Consts.h"
#include <iostream>
 
using namespace std;

// Prints out a helpful usage message
void show_help_message(char* file_name, char* usage_message)
{
	cout << "Help" << endl;
	cout << "usage: " << file_name << usage_message << endl;
}

// Prints out an error message, followed by a helpful message
void show_argument_error_message(char* file_name, char* usage_message)
{
	cout << "Program halted due to invalid argument list" << endl;
	show_help_message(file_name, usage_message);
}

// Parses the argument list and write the paths of files to the strings params
int parse_argument_list(int argc, char* argv[], char* usage_message, string & dictionary_path, string & tile_path)
{
	if (argc == ONE_PARAM) {
		string arg(argv[FIRST_ARG_PARAM]);
		if (arg == "-h" || arg == "-H" || arg == "--help") {
			show_help_message(argv[PROGRAM_NAME_PARAM], usage_message); // Don't shows the error message if the argument is -h
			return HELP_ARGUMENT_EXIT;
		} 
	}
	if (argc != FOUR_PARAMS && argc != TWO_PARAMS) {
		show_argument_error_message(argv[PROGRAM_NAME_PARAM], usage_message);
		return INVALID_ARGUMENT_ERROR;
	}
	for (int i = FIRST_ARG_PARAM; i < argc; i += 2) {
		string arg(argv[i]);
		if (arg == "-d" || arg == "-D") {
			dictionary_path = argv[i + 1];
		} 
		if (arg == "-t" || arg == "-T") {
			tile_path = argv[i + 1];
		}
		if (arg != "-d" && arg != "-D" && arg != "-t" && arg != "-T") {
			show_argument_error_message(argv[PROGRAM_NAME_PARAM], usage_message);
			return INVALID_ARGUMENT_ERROR;
		} 
	}
	if (dictionary_path == "") {
		show_argument_error_message(argv[PROGRAM_NAME_PARAM], usage_message);
		return INVALID_ARGUMENT_ERROR;
	}
	if (tile_path == "") {
		show_argument_error_message(argv[PROGRAM_NAME_PARAM], usage_message);
		return INVALID_ARGUMENT_ERROR;
	}
	return 0;
}