// LetterTileDefinition.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Contains the LetterTileDefinition struct

#ifndef LETTER_TILE_DEFINITION_H
#define LETTER_TILE_DEFINITION_H

#include "stdafx.h"
#include "LetterTile.h"

// struct for the letter tile definition
// this struct represents a LetterTile and counts the occurrences of the letters
struct LetterTileDefinition {
	LetterTile letter_tile;
	unsigned int count;

	LetterTileDefinition(LetterTile l, unsigned int c)
		:letter_tile(l), count(c){}

	// This function should return the letter_tile.letter (law of demeter)
	char get_letter() const; 

	// This operator compares two LetterTileDefinition by verifing which one has the lower count
	// And if the count is the same, which one has de lower letter
	bool operator<(const LetterTileDefinition & other) const;
};

#endif /* LETTER_TILE_DEFINITION_H */