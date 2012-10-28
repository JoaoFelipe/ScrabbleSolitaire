// LetterTileDefinitionCollection.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Contains the LetterTileDefinitionCollection class

#ifndef LETTER_TILE_DEFINITION_COLLECTION_H
#define LETTER_TILE_DEFINITION_COLLECTION_H

#include "stdafx.h"
#include "LetterTileDefinition.h"
#include "Consts.h"
#include "Dictionary.h"
#include <vector>
#include <string>


using namespace std;

// Class that represents a collection of letter tiles definition
// This class is used to generate the tile definitions file
class LetterTileDefinitionCollection {
public:
	// Constructor that takes a const reference to a Dictionary object
	// and populates the _container with new LetterTileDefinitions with score based on the count
	// of each letter in the Dictionary words
	LetterTileDefinitionCollection(const Dictionary & dict);

	// This function will create LetterTile and add it to the _container with the respective counting
	void add(char letter, unsigned int count);

	// This method saves the LetterTileDefinitionCollection to a tiles file 
	int save(const string & tile_path = DEFAULT_TILE_PATH);

	// A destructor is not necessary to releases the dynamically allocated vector,
	// because, when the compiler-supplied destructor is called, it will call the destructor
	// for vector
private:
	vector<LetterTileDefinition> _container;

	// Deleting the assingment operator
	LetterTileDefinitionCollection & operator=(const LetterTileDefinitionCollection &);

	// Deleting the copy constructur
	LetterTileDefinitionCollection(const LetterTileDefinitionCollection &);

};


#endif /* LETTER_TILE_DEFINITION_COLLECTION_H */