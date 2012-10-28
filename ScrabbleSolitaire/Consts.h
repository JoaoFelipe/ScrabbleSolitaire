// Consts.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Declare consts for the program

#ifndef CONSTS_H
#define CONSTS_H

#include "stdafx.h"
#include <string>

using namespace std;

// const for invalid argument error return
static const int INVALID_ARGUMENT_ERROR = 1;
// const for help argument return
static const int HELP_ARGUMENT_EXIT = 2;
// const for any problems that may occur opening input files 
static const int INPUT_FILE_ERROR = 3;
// const for any problems that may occur opening output files 
static const int OUTPUT_FILE_ERROR = 4;
// const for errors that may occur when you don't have enough tiles
static const int NOT_ENOUGH_TILES = 5;
// const for exception that are thrown, but can't be recognized by the main try..catch
static const int UNRECOGNIZED_ERROR = 6;

// const for the program name parameter position
static const int PROGRAM_NAME_PARAM = 0;
// const for the first parameter position
static const int FIRST_ARG_PARAM = 1;
// const for one argument parameter after the program name
static const int ONE_PARAM = 2;
// const for two argument parameters after the program name
static const int TWO_PARAMS = 3;
// const for four argument parameters after the program name
static const int FOUR_PARAMS = 5;

// const for the default tile path name
static const string DEFAULT_TILE_PATH = string("tile_defs.txt");


#endif /* CONSTS_H */
