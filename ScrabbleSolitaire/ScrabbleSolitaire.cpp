// ScrabbleSolitaire.cpp 
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Kaichen Zhang <zkcwustl@gmail.com>
// Defines the entry point for the console application

#include "stdafx.h"
#include "Argument.h"
#include "LetterTileDefinitionCollection.h"
#include "WordCollection.h"
#include "Player.h"
#include "GameBoard.h"

using namespace std;

// Usage message for each program. Since this message may change between the labs, 
// I preferred to put it in here instead of putting in the Consts.h
static char* USAGE_MESSAGE = 	
	" -d <dictionary file> -t <tile definition file>\n"
	"This program reads the dictionary file and the tile definition file. Then it randomly separes the letter tiles in three hands with 7 tiles each and shows valid words that can be made with these hands\n"
	"If the tile definition file doesn't exist, it will be generated by the dictionary file\n"
	"    -h|-H: show this help message\n"
	"    -d|-D <dictionary file>: path to the dictionary file\n"
	"    -t|-T <tile definition file>: path to the tile definition file\n";



int main(int argc, char* argv[])
{
	try {
		GameBoard game_board;
		game_board.print();

		string dictionary_path, tile_path;
		int error_code = 0;
	
		error_code = parse_argument_list(argc, argv, USAGE_MESSAGE, dictionary_path, tile_path);
		if (error_code != 0) {
			if (error_code == HELP_ARGUMENT_EXIT) {
				return 0;
			}
			return error_code;
		}

		Dictionary dict(dictionary_path);
		if (dict.size() == 0) {
			cout << "The dictionary file '" << dictionary_path << "' couldn't be opened or don't have any words" << endl;
			return error_code;
		}

		LetterTileCollection letter_tile_collection(tile_path);
		if (letter_tile_collection.size() == 0) {
			cout << "The tile definition file '" << tile_path << "' couldn't be opened or don't have any tile definitions. A new one will be generated." << endl;
			LetterTileDefinitionCollection def_collection(dict);
			int e = def_collection.save(tile_path);
			if (e != 0) {
				cout << "The tile definition file '" << tile_path << "' couldn't be saved" << endl;
				return e;
			}
			letter_tile_collection = LetterTileCollection(tile_path);
		}

		if (letter_tile_collection.size() < 21) {
			cout << "You need at least 21 letter tiles to execute this program" << endl;
			return NOT_ENOUGH_TILES;
		}

		vector<LetterTileCollection> hands(3);
		for (unsigned int i = 0; i < hands.size(); ++i) {
			LetterTileCollection & hand = hands[i];
			letter_tile_collection.shuffle();
			hand.move(letter_tile_collection, 7);
			WordCollection wc(hand, dict);
			cout << endl << "Hand " << i+1 << " - " << hand.as_string() << ": " << endl;
			wc.print();
		}
	} catch (int e) {
		cout << "Error code: " << e << endl;
		return e;
	} catch (...) {
		cout << "Unrecognized error" << endl;
		return UNRECOGNIZED_ERROR;
	}
	return 0;
}
