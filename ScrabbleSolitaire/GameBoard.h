// GameBoard.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Kaichen Zhang <zkcwustl@gmail.com>
// Contains the GameBoard class

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "LetterTile.h"
#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include "Player.h"
#include "Dictionary.h"
#include "LetterTileCollection.h"


using namespace std;

// Class that represents a game board
class GameBoard {
public:
	// Default constructor: constructs a GameBoard with a 15x15 _board
	GameBoard ();
	// Copy constructor: constructs a copy of a gameboard with their LetterTile. LetterTiles are created by new
	GameBoard (GameBoard & gb);
	// Destructor: deletes all the LetterTiles
	~GameBoard ();
	// This method prints out a board with the letter tiles
	void print(ostream & = cout)const;
	// This method first simulates a play and if it is valid, it completes the play and changes the word. If not, it tries to play the sequence in all positions of the board to suggest a valid play
	unsigned int play(const Dictionary & dict, const LetterTileCollection & ltc, pair<int, int> position, enum Direction direction); 
private:
	// This method clone the LetterTile of a board into this 
	void clone(GameBoard & gb);
	// This method erases all the LetterTiles of _board
	void erase();
	// This methods returns true if the board is empty (assuming that the center position (0, 0) is empty
	bool first_play();
	// This method get all adjacent letter tiles in one direction (vertical\horizontal) and adds it to a LetterTileCollection
	int get_word(pair<int, int> & position, LetterTileCollection & ltc, enum Direction direction);
	// This method clones the current game board and simulates a play on it. If the play is valid, it returns the score of the play. If not, it returns 0
	unsigned int simulates_play(GameBoard & clone, const Dictionary & dict, const LetterTileCollection & ltc, pair<int, int> position, enum Direction direction, ostream & output = cout); 
	
	// This is a 15x15 board of LetterTiles
	map<pair<int,int>, LetterTile*> _board;
};

#endif /* GAME_BOARD_H */