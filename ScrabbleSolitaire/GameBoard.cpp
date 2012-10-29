// LetterTileCollection.cpp
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Kaichen Zhang <zkcwustl@gmail.com>
// Defines methods of GameBoard

#include "stdafx.h"
#include "GameBoard.h"
#include <string>
#include <sstream>
#include "Consts.h"

using namespace std;



	
// const for error message when the first play is in the wrong position
char* ERROR_FIRST_PLAY_WRONG_POSITION = 	
	"The first play on an empty board should be on the position (0, 0)";

// const for error message when the play doesn't intersects any tile in the board
char* ERROR_PLAY_DOESNT_INTERSEPT_TILE = 	
	"The play must intersect with at least one existing tile";

// const for the error messsage when the position is out of bounds
char* ERROR_POSITION_OUT_OF_BOUND =
	"The position reached is out of bound";

// const for error message when the play generates invalid words
char* ERROR_INVALID_POSITION =
	"This position generates invalid words";



// Default constructor: constructs a GameBoard with a 15x15 _board
GameBoard::GameBoard(): _board() {	
	for (int y = MIN_Y; y <= MAX_Y; ++y) {
		for (int x = MIN_X; x <= MAX_X; ++x) {
			pair<int, int> p(y, x); 
			_board[p] = EMPTY_TILE;
		}
	}
}

// Copy constructor: constructs a copy of a gameboard with their LetterTile. LetterTiles are created by new
GameBoard::GameBoard(GameBoard & gb): _board() {	
	clone(gb);
}

// Destructor: deletes all the LetterTiles
GameBoard::~GameBoard() {	
	erase();
}

// This method clone the LetterTile of a board into this 
void GameBoard::clone(GameBoard & gb) {
	for (int y = MIN_Y; y <= MAX_Y; ++y) {
		for (int x = MIN_X; x <= MAX_X; ++x) {
			pair<int, int> p(y, x); 
			if (gb._board.at(p) != EMPTY_TILE) {
				_board[p] = new LetterTile(*gb._board.at(p));
			} else {
				_board[p] = EMPTY_TILE;
			}	
		}
	}
}

// This method erases all the LetterTiles of _board
void GameBoard::erase() {
	for (map<pair<int,int>, LetterTile*>::iterator i = _board.begin(); i != _board.end(); ++i) {
		delete i->second;
	}
}

// This method prints out a board with the letter tiles
void GameBoard::print(ostream &o) const{
	string s = " 765432101234567 ";
	o << s << endl;

	for (int y = MAX_Y; y >= MIN_Y; --y) {
		o << abs(y);
		for (int x = MIN_X; x <= MAX_X; ++x) {
			pair<int, int> p(y, x); 
			LetterTile * lt = _board.at(p);
			if (lt != EMPTY_TILE) {
				o << lt->letter;
			} else {
				o << " ";
			}
		}
		o << abs(y) << endl;
	}
	o << s << endl;
}

// This methods returns true if the board is empty (assuming that the center position (0, 0) is empty
bool GameBoard::first_play() {
	pair<int, int> zero(0,0);
	return _board.at(zero) == EMPTY_TILE;
}

// This method get all adjacent letter tiles in one direction (vertical\horizontal) and adds it to a LetterTileCollection
int GameBoard::get_word(pair<int, int> & position, LetterTileCollection & ltc, enum Direction direction) {
	int i(position.first), j(position.second), min(8), max(-8);
	pair<int, int> * current_position = new pair<int, int>(i, j);
	//Find min position going up or left until it finds an empty tile
	while (i <= MAX_Y && j >= MIN_X && _board[*current_position] != EMPTY_TILE) {
		if (direction == horizontal) {
			min = j;
			j--;
		} else {
			min = i;
			i++;
		}
		delete current_position;
		current_position = new pair<int, int>(i, j);
	}
	if (direction == horizontal) {
		j = min;
	} else {
		i = min;
	}
	delete current_position;
	current_position = new pair<int, int>(i, j);
	//Find max position, going down or right until it finds an empty tile, adding lettertiles to LetterTileCollection
	while (i >= MIN_Y && j <= MAX_X && _board[*current_position] != EMPTY_TILE) {
		if (direction == horizontal) {
			max = j;
			j++;
		} else {
			max = i;
			i--;
		}
		ltc.insert(*_board[*current_position]);
		delete current_position;
		current_position = new pair<int, int>(i, j);
	}
	delete current_position;
	return ltc.score();
}

// This method clones the current game board and simulates a play on it. If the play is valid, it returns the score of the play. If not, it returns 0
unsigned int GameBoard::simulates_play(GameBoard & clone, const Dictionary & dict, const LetterTileCollection & ltc, pair<int, int> position, enum Direction direction, ostream & output) {
	clone.clone(*this);
	pair<int, int> zero(0,0);
	int i(position.first), j(position.second);
	unsigned int ltc_position = 0;
	unsigned int score = 0;
	// It should check if the word intersects on LetterTile in the board
	// If it is the first play, it shouldn't intersect
	bool intersect_tile = first_play();
	// It should check if the word intersects the position (0, 0) when it is the first play
	// When it is not the first play, it shoudn't intersect
	bool first_play_intersect_zero = !first_play(); 

	pair<int, int> left(i, j-1);
	if (direction == horizontal && j > MIN_X && j <= MAX_X && i <= MAX_Y && i >= MIN_Y && _board.at(left) != EMPTY_TILE) {
		intersect_tile = true;
	}

	pair<int, int> up(i+1, j);
	if (direction == vertical && i < MAX_Y && i >= MIN_Y && j >= MIN_X && j <= MAX_X && _board.at(up) != EMPTY_TILE) {
		intersect_tile = true;
	}
	pair<int, int> * current_position = new pair<int, int>(i, j);
	// This will add the letters of the LetterTileCollection in the board until all letters are used
	while (ltc.size() != ltc_position) {
		// If there is more letters than it is possible to add, or if the position played is out of bounds:
		if (j < MIN_X || i < MIN_Y || j > MAX_X || i > MAX_Y) {
			output << ERROR_POSITION_OUT_OF_BOUND << " (" << j << ", " << i << ")" << endl; 
			return ERROR_PLAY;
		}

		delete current_position;
		current_position = new pair<int, int>(i, j);

		if (first_play() && *current_position == zero) {
			first_play_intersect_zero = true;
		} 
		// If find an empty tile in the board
		if (_board.at(*current_position) == EMPTY_TILE) {
			// Add it to the clone board
			clone._board[*current_position] = ltc[ltc_position];
			ltc_position++;
			// And check for perpendicular words adding the scores of them
			LetterTileCollection collection;
			int value;
			if (direction == horizontal) {
				value = clone.get_word(*current_position, collection, vertical);
			} else {
				value = clone.get_word(*current_position, collection, horizontal);
			}		
			if (collection.size() > 1 && dict.find(collection.as_string())) {
				score += value;
				intersect_tile = true;
			} else if (collection.size() > 1) {
				//The perpendicular word isn't valid
				output << ERROR_INVALID_POSITION << endl;
				return ERROR_PLAY;
			}
		} else {			
			intersect_tile = true;
		}
		//Moves to next position in board
		if (direction == horizontal) {
			j++;
		} else {
			i--;
		}
	}
	delete current_position;
	current_position = new pair<int, int>(i, j);
	//if the next position in the board is a letter tile, the play intercects a tile
	if (i >= MIN_Y && j <= MAX_X && _board.at(*current_position) != EMPTY_TILE) {
		intersect_tile = true;
	}
	delete current_position;

	if (!first_play_intersect_zero) {
		output << ERROR_FIRST_PLAY_WRONG_POSITION << endl;
		return ERROR_PLAY;
	}
	if (!intersect_tile) {
		output << ERROR_PLAY_DOESNT_INTERSEPT_TILE << endl;
		return ERROR_PLAY;
	}
	//Check if the word in the played direction is valid
	LetterTileCollection collection;
	int value(clone.get_word(position, collection, direction));	
	if (collection.size() > 1 && dict.find(collection.as_string())) {
		score += value;
	} else if (collection.size() > 1) {
		output << ERROR_INVALID_POSITION << endl;
		return ERROR_PLAY;
	}
	
	return score;
}

// This method first simulates a play and if it is valid, it completes the play and changes the word. If not, it tries to play the sequence in all positions of the board to suggest a valid play
unsigned int GameBoard::play(const Dictionary & dict, const LetterTileCollection & ltc, pair<int, int> position, enum Direction direction) {
	GameBoard c;
	unsigned int result = simulates_play(c, dict, ltc, position, direction, cout);
	if (result != ERROR_PLAY) {
		this->erase();
		this->clone(c);
		return result;	
	} else {
		for (int i = MIN_Y; i <= MAX_Y; ++i) {
			for (int j = MIN_X; j <= MAX_X; ++j) {
				pair<int, int> p(i,j); 
				
				ostringstream s;
				if (j <= MAX_X - (int) ltc.size()) {
					GameBoard c;
					
					unsigned int value = simulates_play(c, dict, ltc, p, horizontal, s);
					if (value != ERROR_PLAY) {
						cout << "You should try to play in the position (" << j << ", " << i << ") horizontal" << endl;
						return ERROR_PLAY;
					}
				}
				if (i >= MIN_Y + (int) ltc.size()) {
					GameBoard c;				
					unsigned int value = simulates_play(c, dict, ltc, p, vertical, s);
					if (value != ERROR_PLAY) {
						cout << "You should try to play in the position (" << j << ", " << i << ") vertical" << endl;
						return ERROR_PLAY;
					}
				}
				
			}
		}
	}
	
	cout << "There is no valid play for the sequence given. Try a different sequence" << endl;
	return ERROR_PLAY;
}