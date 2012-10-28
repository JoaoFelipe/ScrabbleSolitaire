// LetterTileCollection.cpp
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Kaichen Zhang <zkcwustl@gmail.com>
// Defines methods of GameBoard

#include "stdafx.h"
#include "GameBoard.h"
#include <string>

using namespace std;

char* ERROR_FIRST_PLAY_WRONG_POSITION = 	
	"The first play on an empty board should be on the position (0, 0)";

char* ERROR_PLAY_DOESNT_INTERSEPT_TILE = 	
	"The play must intersect with at least one existing tile";

char* ERROR_POSITION_OUT_OF_BOUND =
	"The position reached is out of bound";

const int EMPTY_TILE = 0;

GameBoard::GameBoard(): _board() {	
	for (int i = -7; i <= 7; ++i) {
		for (int j = -7; j <= 7; ++j) {
			pair<int, int> p(i,j); 
			_board[p] = EMPTY_TILE;
		}
	}
}

GameBoard::GameBoard(GameBoard & gb): _board() {	
	for (int i = -7; i <= 7; ++i) {
		for (int j = -7; j <= 7; ++j) {
			pair<int, int> p(i,j); 
			if (gb._board.at(p) != EMPTY_TILE) {
				_board[p] = new LetterTile(*gb._board.at(p));
			} else {
				_board[p] = EMPTY_TILE;
			}	
		}
	}
}

GameBoard::~GameBoard() {	
	for (map<pair<int,int>, LetterTile*>::iterator i = _board.begin(); i != _board.end(); ++i) {
		delete i->second;
	}
}

void GameBoard::print(ostream &o) const{
	string s = " 765432101234567 ";
	cout << s << endl;

    for (int i = -7; i <= 7; ++i) {
		cout << abs(i);
		for (int j = -7; j <= 7; ++j) {
			pair<int, int> p(i,j); 
			LetterTile * lt = _board.at(p);
			if (lt != EMPTY_TILE) {
				cout << lt->letter;
			} else {
				cout << " ";
			}
		}
		cout << abs(i) << endl;
	}
	cout << s << endl;

}

bool GameBoard::first_play() {
	pair<int, int> zero(0,0);
	return _board.at(zero) == 0;
}

bool GameBoard::intersects_tile(pair<int, int> position) {
	int i(position.first), j(position.second);
	
	pair<int, int> left(i, j - 1);
	pair<int, int> right(i, j + 1);
	pair<int, int> up(i - 1, j);
	pair<int, int> down(i + 1, j);

	bool result = false;
	result |= (i > -7 && _board.at(up) != EMPTY_TILE);
	result |= (i < 7 && _board.at(down) != EMPTY_TILE);
	result |= (j > -7 && _board.at(left) != EMPTY_TILE);
	result |= (j < 7 && _board.at(right) != EMPTY_TILE);
	return result;
}

unsigned int GameBoard::play(const Dictionary & dict, const LetterTileCollection & ltc, pair<int, int> position, enum Direction direction) {
	GameBoard clone(*this);
	pair<int, int> zero(0,0);
	int i(position.first), j(position.second);
	int ltc_position = 0;
	
	bool intersect_tile = false;
	bool first_play_intersect_zero = !first_play();

	while (ltc.size() != ltc_position) {
		if (j < -7 || i < -7 || j > 7 || i > 7) {
			cout << ERROR_POSITION_OUT_OF_BOUND << " (" << i << ", " << j << ")" << endl; 
			return 0;
		}

		pair<int, int> current_position(i, j);

		if (first_play() && current_position == zero) {
			first_play_intersect_zero = true;
		} 

		if (_board.at(current_position) == EMPTY_TILE) {
			clone._board[current_position] = ltc[ltc_position];
			ltc_position++;
			if (intersects_tile(current_position)) {
				intersect_tile = true;
				
				//TODO: Check the word around the intersected tile if it is perpendicular of the direction
			}
		} else {
			intersect_tile = true;
		}

		if (direction == horizontal) {
			j++;
		} else {
			i++;
		}
	}
	
	if (!first_play_intersect_zero) {
		cout << ERROR_FIRST_PLAY_WRONG_POSITION << endl;
		return 0;
	}
	if (!intersect_tile) {
		cout << ERROR_PLAY_DOESNT_INTERSEPT_TILE << endl;
		return 0;
	}

	//TODO: Check the word in the direction


}