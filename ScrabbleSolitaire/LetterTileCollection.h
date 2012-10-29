// LetterTileCollection.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Kaichen Zhang <zkcwustl@gmail.com>
// Contains the LetterTileCollection class

#ifndef LETTER_TILE_COLLECTION_H
#define LETTER_TILE_COLLECTION_H

#include "stdafx.h"
#include "LetterTile.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Class that represents a collection of letter tiles
class LetterTileCollection {
public:
	// Default constructor in LetterTileCollection that initializes a empty container
	LetterTileCollection ();

	// Copy Constructor that takes a reference to another letter tile collection object and
	// initializes itself to contain the same sequence of letter tiles
	LetterTileCollection (const LetterTileCollection & other);

	// Constructor that takes a file name and reads it into container
	LetterTileCollection (const string & filename);

	// Constructor that takes a reference to another letter tile collection object and
	// a reference to a string, and initializes itself to contain the same sequence of letters 
	// of the word if it is possible to do using the letters of the collection
	// When it is not possible, initializes a empty container
	LetterTileCollection (const LetterTileCollection & other, const string & word);

	// Assignment operator
	LetterTileCollection& operator=(LetterTileCollection const & other);

	// This method returns the number of elements in the container
	unsigned int size() const;

	// This method takes a file name, opens up the file, reads in strings and inserts them into _container 
	// The file structure should be the following:
	// Each line define tiles of one letter with the informations
	// letter score occurrences
	int add(const string & filename);

	// This method moves the last n tiles from other LetterTileCollection to 
	// this LetterTileCollection
	void move(LetterTileCollection & other, unsigned int n);


	// This method finds a word in the container
	bool find(string & word) const;

	// This method prints to ostream each tile on the LetterTileCollection
	void print(ostream & stream = cout) const;
	
	// Equivalent operator: verifies if the another LetterTileCollection has exactly the same sequence of letter tiles
	bool operator==(LetterTileCollection const & other) const;

	// Less than: verifies if the sum of scores of tiles in this LetterTileCollection
	// is less than the sum of the scores of tiles in the other LetterTileCollection 
	bool operator<(LetterTileCollection const & other) const;

	// This method randomly rearranges the sequence of letter tiles in the container
	void shuffle();

	// This method rearranges the sequence of letter tiles in the container into its
	// next lexicographically greater permutation
	bool permute();

	// This method returns a c++ string containing the sequence of letters represented by the sequence of tiles in the container 
	string as_string() const;

	// This method returns the sum of the scores of tiles in the container 
	unsigned int score() const;

	// Sort the LetterTileCollection
	void msort();

	// A destructor is not necessary to releases the dynamically allocated vector,
	// because, when the compiler-supplied destructor is called, it will call the destructor
	// for vector

	// Returns a pointer to a new LetterTile from the container (lab4)
	LetterTile* operator[](int position) const;

	// This method takes a LetterTile and push it back into the _container
	void insert(LetterTile & lt);

	// This method takes a LetterTileCollection and push back the LetterTile in the position into the _container (Lab4)
	void insert(const LetterTileCollection & lt, int position);

	// This method removes the LetterTiles from this LetterTileCollection if they are present in a given string (Lab4)
	// Returns 0 if sucessful
	int remove(string & word);

private:
	// Private container of strings
	vector<LetterTile> _container;
};

#endif /* LETTER_TILE_COLLECTION_H */