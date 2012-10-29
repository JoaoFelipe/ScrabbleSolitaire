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
#include <cctype>
#include <algorithm>
#include <string>

using namespace std;

// Usage message for each program. Since this message may change between the labs, 
// I preferred to put it in here instead of putting in the Consts.h
static char* USAGE_MESSAGE = 	
	" -d <dictionary file> -t <tile definition file>\n"
	"This program reads the dictionary file and the tile definition file into a pool. Then it moves 7 tiles from the pool to the players hand and allows the player to play Scrabble\n"
	"    -h|-H: show this help message\n"
	"    -d|-D <dictionary file>: path to the dictionary file\n"
	"    -t|-T <tile definition file>: path to the tile definition file\n";



int main(int argc, char* argv[])
{
	try {		
		string dictionary_path, tile_path;
		int error_code = 0;
		//Check the command line arguments
		error_code = parse_argument_list(argc, argv, USAGE_MESSAGE, dictionary_path, tile_path);
		if (error_code != 0) {
			if (error_code == HELP_ARGUMENT_EXIT) {
				return 0;
			}
			return error_code;
		}
		//Read the dictionary file
		Dictionary dict(dictionary_path);
		if (dict.size() == 0) {
			cout << "The dictionary file '" << dictionary_path << "' couldn't be opened or don't have any words" << endl;
			return INVALID_DICTIONARY_ERROR;
		}
		//Read the LetterTileDefinition file into pool
		LetterTileCollection pool(tile_path);
		//If the file doesn't exist, generates a new one from the dictionary
		if (pool.size() == 0) {
			cout << "The tile definition file '" << tile_path << "' couldn't be opened or don't have any tile definitions. A new one will be generated." << endl;
			LetterTileDefinitionCollection def_collection(dict);
			int e = def_collection.save(tile_path);
			if (e != 0) {
				cout << "The tile definition file '" << tile_path << "' couldn't be saved" << endl;
				return e;
			}
			pool = LetterTileCollection(tile_path);
		}

		GameBoard game_board;
		unsigned int score = 0;
		LetterTileCollection player;

		pool.shuffle();
		//LetterTileCollection player(pool, "AGAINST");
		
		player.move(pool, 7);


		while (player.size() != 0) {
			game_board.print();
			player.print();
			cout << "Score: " << score << endl;
			char answer;
			cout << "Do you wanna play? (Y/N)" << endl;
			cin >> answer;
			answer = toupper(answer);
			if (answer == 'R') {
				pool.move(player, player.size());
				pool.shuffle();
				player.move(pool, 7);
			} else
			if (answer == 'Y') {
				cout << "Type your word using your tiles:" << endl;
				string word;
				cin >> word;
				transform(word.begin(), word.end(),word.begin(), ::toupper);
				LetterTileCollection wltc(player, word);
				if (wltc.size() == 0) {
					cout << "The given word isn't valid" << endl;
					continue;
				} else {
					int x, y;
					cout << "Position: Write X" << endl;
					cin >> x;
					cout << "Position: Write Y" << endl;
					cin >> y;
					pair<int, int> position(y, x);

					cout << "Which direction:" << endl << "  H: Horizontal" << endl << "  V: Vertical " << endl;
					cin >> answer;
					answer = toupper(answer);
					int value;
					if (answer == 'H') {
						value = game_board.play(dict, wltc, position, horizontal);
					} else {
						value = game_board.play(dict, wltc, position, vertical);
					}
					if (value != ERROR_PLAY) {
						if (word.size() == 7) {
							score += 50;
							cout << "Extra 50 points for using all 7 tiles." << endl;
						}
						player.remove(word);
						player.move(pool, word.size());
						score += value;
					}
				}
			} else if (answer == 'N') {
				return SUCCESS;
			}
		}

		game_board.print();
		player.print();
		cout << "Score: " << score << endl;
		cout << "No remaining tiles left." << endl;

		

	
	} catch (int e) {
		cout << "Error code: " << e << endl;
		return e;
	} catch (...) {
		cout << "Unrecognized error" << endl;
		return UNRECOGNIZED_ERROR;
	}
	return SUCCESS;
}

