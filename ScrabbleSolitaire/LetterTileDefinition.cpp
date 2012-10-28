// LetterTileDefinition.cpp
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Defines the functions of the LetterTileDefinition Struct

#include "stdafx.h"
#include "LetterTileDefinition.h"

// Returns the letter from the letter_tile of the LetterTileDefinition
char LetterTileDefinition::get_letter() const {
	return letter_tile.letter;
}

// Compare two LetterTileDefinition
// Return true if count of the first < count of the second
// if both are equal, return true if letter of the first < letter of the second
bool LetterTileDefinition::operator<(const LetterTileDefinition & other) const {
	return (count < other.count || 
		(count == other.count && get_letter() < other.get_letter()));
}


