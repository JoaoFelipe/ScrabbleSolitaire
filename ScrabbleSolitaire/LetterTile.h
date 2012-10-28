// LetterTile.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Contains the LetterTile struct

#ifndef LETTER_TILE_H
#define LETTER_TILE_H

#include "stdafx.h"

// struct for the letter tiles
// this struct represents a letter and a score for the letter
struct LetterTile {
	char letter;
	unsigned int score;

	LetterTile(char l, unsigned int s);
	
	// Verifies if the letter of this LetterTile is lexicographically less than the 
	// letter of other LetterTile
	// If it is the same letter, verifies the score
	bool operator<(LetterTile & other);
};


#endif /* LETTER_TILE_H */