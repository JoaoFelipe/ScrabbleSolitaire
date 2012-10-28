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
	GameBoard ();
	GameBoard (GameBoard & gb);
	~GameBoard ();
	void print(ostream & = cout)const;
	bool first_play();
	bool intersects_tile(pair<int, int> position);

	unsigned int play(const Dictionary & dict, const LetterTileCollection & ltc, pair<int, int> position, enum Direction direction); 
private:

	map<pair<int,int>, LetterTile*> _board;
};

#endif /* GAME_BOARD_H */