// Dictionary.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Contains the Dictionary class

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "stdafx.h"
#include <string>
#include <set>
#include <iostream>

using namespace std;

// Class that represents a Dictionary
class Dictionary {
	friend class WordCollection;
	friend class LetterTileDefinitionCollection;
public:
	// Default constructor in Dictionary that initializes a empty container
	Dictionary ();

	// Constructor that takes a file name and reads it into container
	Dictionary (const string & filename);

	// This method takes a file name, opens up the file, reads in strings and inserts them into _container 
	int add(const string & filename);

	// This method returns the number of elements in the container
	int size() const;

	// This method finds a word in the container
	bool find(const string & word) const;

	// This method prints to ostream each string on the dictionary
	void print(ostream & stream = std::cout) const;

	// A destructor is not necessary to releases the dynamically allocated vector,
	// because, when the compiler-supplied destructor is called, it will call the destructor
	// for vector
private:
	// Private container of strings
	set<string> _container;

	// Deleting the assingment operator
	Dictionary & operator=(const Dictionary &);

	// Deleting the copy constructur
	Dictionary(const Dictionary &);
};

#endif /* DICTIONARY_H */