// LetterTile.cpp
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Defines the LetterTile struct functions

#include "stdafx.h"
#include "LetterTile.h"


LetterTile::LetterTile(char l, unsigned int s):letter(l), score(s){}
	

// Verifies if the letter of this LetterTile is lexicographically less than the 
// letter of other LetterTile
// If it is the same letter, verifies the score
bool LetterTile::operator<(LetterTile & other) {
	return (letter < other.letter) || 
		(letter == other.letter && score < other.score);

}