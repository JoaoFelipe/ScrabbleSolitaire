// Consts.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Declare consts for the program

#ifndef CONSTS_H
#define CONSTS_H

#include "stdafx.h"
#include <string>

using namespace std;

// const for invalid argument error return
const int INVALID_ARGUMENT_ERROR = 1;
// const for help argument return
const int HELP_ARGUMENT_EXIT = 2;
// const for any problems that may occur opening input files 
const int INPUT_FILE_ERROR = 3;
// const for any problems that may occur opening output files 
const int OUTPUT_FILE_ERROR = 4;
// const for errors that may occur when you don't have enough tiles
const int NOT_ENOUGH_TILES = 5;
// const for exception that are thrown, but can't be recognized by the main try..catch
const int UNRECOGNIZED_ERROR = 6;
// const for invalid dictionary error
const int INVALID_DICTIONARY_ERROR = 7;
// const for invalid word error
const int INVALID_WORD_ERROR = 8;


// const for the program name parameter position
const int PROGRAM_NAME_PARAM = 0;
// const for the first parameter position
const int FIRST_ARG_PARAM = 1;
// const for one argument parameter after the program name
const int ONE_PARAM = 2;
// const for two argument parameters after the program name
const int TWO_PARAMS = 3;
// const for four argument parameters after the program name
const int FOUR_PARAMS = 5;

// const for the default tile path name
const string DEFAULT_TILE_PATH = string("tile_defs.txt");

// const for success
const int SUCCESS = 0;


// const to indicate an empty tile
const int EMPTY_TILE = 0;
// const for error in the play method
const int ERROR_PLAY = 0;

// const for min board X position
const int MIN_X = -7;
// const for max board X position
const int MAX_X = 7;

// const for min board Y position
const int MIN_Y = -7;
// const for max board Y position
const int MAX_Y = 7;


#endif /* CONSTS_H */
