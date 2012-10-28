// LetterTileDefinitionCollection.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Defines the LetterTileDefinitionCollection methods

#include "stdafx.h"
#include "LetterTileDefinitionCollection.h"
#include <algorithm>
#include <fstream>


// Creates a LetterTile and adds it to the LetterTileDefinitionCollection
void LetterTileDefinitionCollection::add(char letter, unsigned int count) {
	if (letter != '\0') {
		LetterTile letter_tile(letter, 0);
		LetterTileDefinition def(letter_tile, count);
		_container.push_back(def);
	}
}

// Constructs a LetterTileDefinitionCollection by a Dictionary
LetterTileDefinitionCollection::LetterTileDefinitionCollection(const Dictionary & dict): _container() {
	string all_letters;
	for (set<string>::const_iterator i = dict._container.begin(); i != dict._container.end(); ++i) {
		all_letters +=  *i; //Concat all words of the dictionary
	}
	sort(all_letters.begin(), all_letters.end()); //Sort the letters
	
	char current_letter = '\0';
	unsigned int current_count = 0;
	for (unsigned int i = 0; i < all_letters.size(); ++i) { //count groups of letters and add to the _container
		char current = all_letters[i];
		if (current != current_letter) {
			add(current_letter, current_count); 
			current_letter = current;
			current_count = 1;
		} else {
			++current_count;
		}
	}
	add(current_letter, current_count);

	sort(_container.rbegin(), _container.rend()); //Sort _container reversed by count of letters in LetterTileDefinition
	for (unsigned int i = 0; i < _container.size(); ++i) {
		LetterTileDefinition & tile_definition = _container[i];
		tile_definition.letter_tile.score = i + 1; //Set score for each letter
	}
}

// Saves the LetterTileDefinitionCollection to a tiles file 
// Returns OUTPUT_FILE_ERROR if it is not possible to open the file
int LetterTileDefinitionCollection::save(const string & tile_path) {
	ofstream ofs(tile_path.c_str());
	if (ofs.is_open()) {
		for (unsigned int i = 0; i < _container.size(); ++i) {
			const LetterTileDefinition & tile_definition = _container[i];
			const LetterTile & tile = tile_definition.letter_tile;
			ofs << tile.letter << " " << tile.score << " " << tile_definition.count << endl;
		}
		ofs.close();
	} else {
		return OUTPUT_FILE_ERROR;
	}
	return 0;
}


