// Argument.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Contains functions related to the program argument help usage message

#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "stdafx.h"
#include <string>

using namespace std;

// This function prints out a helpful usage to 
// the program's standard output stream 
// The param file_name should be the argv[0]
// The param usage_message should be the help message
void show_help_message(char* file_name, char* usage_message);

// This function prints out an error message
// telling that the argument format is invalid
// and, then prints the help message 
// The param file_name should be the argv[0
// The param usage_message should be the help message
void show_argument_error_message(char* file_name, char* usage_message);

// This function parses the argument list
// received by the params argv and argc and the help usage message
// and attributes the dictionary and tile definition paths
// to the params dictionary_path and tile_path
// if there is an error in the argument list, the 
// function returns INVALID_ARGUMENT_ERROR
int parse_argument_list(int argc, char* argv[], char* usage_message, string & dictionary_path, string & tile_path);

#endif /* ARGUMENT_H */