// LetterTileCollection.cpp
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Kaichen Zhang <zkcwustl@gmail.com>
// Defines methods of LetterTileCollection

#include "stdafx.h"
#include "LetterTileCollection.h"
#include "Consts.h"
#include "time.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Default constructor in LetterTileCollection that initializes a empty container
LetterTileCollection::LetterTileCollection () 
	: _container() { }

// Copy constructor in LetterTileCollection that copies the sequence of LetterTiles
LetterTileCollection::LetterTileCollection (const LetterTileCollection & other) { 
	_container = vector<LetterTile>(other._container.begin(), other._container.end());
}

// Constructor that takes a file name and reads it into container
LetterTileCollection::LetterTileCollection (const string & filename) 
	: _container() { 
	if (add(filename) != 0) {
		_container = vector<LetterTile>();
	}
}

// Constructor that takes a reference to another letter tile collection object and a reference to a string and spell the string with the letters of the letter tile collection
LetterTileCollection::LetterTileCollection (const LetterTileCollection & other, const string & word) : _container() { 
	vector<bool> used(other._container.size(), false); // this vector indicates which letters were already used
	bool found = true;
	for (unsigned int i = 0; i < word.length() && found; ++i) {
		char ch = word[i];
		found = false;
		// Scan for a not used letter in the other container. If it is found, adds to container
		for (int j = 0; j < other.size(); ++j) {
			if (!used[j] && other._container[j].letter == ch) {
				_container.push_back(other._container[j]);
				used[j] = true;
				found = true;
				j = other.size();
			}
		}
	}
	if (!found) {
		_container = vector<LetterTile>();
	}
}

// LetterTileCollection assigment operator. Puts the sequence of LetterTiles of the assigned object in this object
LetterTileCollection& LetterTileCollection::operator= (LetterTileCollection const & other) {
	if (this == &other) { // checking for self-assignment
		return *this;
	}
	_container.clear(); 
	_container = vector<LetterTile>(other._container.begin(), other._container.end());
	return *this;
}

// Returns the number of elements in container
int LetterTileCollection::size() const {
	return _container.size();
}

// Reads a dictionary file to the container
// Returns INPUT_FILE_ERROR if fails to open file
int LetterTileCollection::add(const string & filename) {
	ifstream ifs(filename.c_str());
	if (ifs.is_open()) {
		while (!ifs.eof()) {
			string line;
			getline(ifs, line);
			
			istringstream iss(line);
			string letter;
			int number(0), score(0);
			
			if (line.length() > 0) {
				iss >> letter;
				iss >> score;
				iss >> number;
				LetterTile tile(letter.at(0), score);
				for (int i = 0; i < number; ++i) {
					_container.push_back(tile);
				}
			}
		}
		ifs.close();
	} else {
		//cout << "The tile definition file '" << tile_path << "' coudn't be opened" << endl;
		return INPUT_FILE_ERROR;
	}
	return 0;
}

// Moves the last n tiles from other LetterTileCollection to this LetterTileCollection
void LetterTileCollection::move(LetterTileCollection & other, unsigned int n) {
	for (vector<LetterTile>::const_iterator i = other._container.end() - n; i < other._container.end(); ++i) {
		_container.push_back(*i);
	}
	other._container.erase(other._container.end() - n, other._container.end());
}

// Prints all _container contents to stream
void LetterTileCollection::print(ostream & stream) const {
	for (vector<LetterTile>::const_iterator i = _container.begin(); i < _container.end(); ++i) {
		stream << i->letter << " - " << i->score << endl;
	}
}

// LetterTileCollection equivalence operator. Verifies if the another LetterTileCollection has exactly the same sequence of letter tiles
bool LetterTileCollection::operator== (LetterTileCollection const & other) const {
	if (size() != other.size()) {
		return false;
	}
	for (vector<LetterTile>::const_iterator i = _container.begin(),  j = other._container.begin(); i < _container.end(); ++i, ++j) {
		if (i->letter != j->letter || i->score != j->score) {
			return false;
		}
	}
	return true;
}

// LetterTileCollection Less than operator: verifies if the sum of scores of tiles in this LetterTileCollection
// is less than the sum of the scores of tiles in the other LetterTileCollection 
bool LetterTileCollection::operator<(LetterTileCollection const & other) const {
	return score() < other.score();
}

// Randomly rearranges the sequence of letter tiles in the container
void LetterTileCollection::shuffle() {
	srand((unsigned int) time(NULL)); //Really random  shuffle
	random_shuffle(_container.begin(), _container.end());
}

// Rearranges the sequence of letter tiles in the container into its
// next lexicographically greater permutation
bool LetterTileCollection::permute() {
	return next_permutation(_container.begin(), _container.end());
}

// Returns a c++ string containing the sequence of letters represented by the sequence of tiles in the container 
string LetterTileCollection::as_string() const {
	string result = "";
	for (vector<LetterTile>::const_iterator i = _container.begin(); i < _container.end(); ++i) {
		result += i->letter;
	}
	return result;
}

// Returns the sum of the scores of tiles in the container 
unsigned int LetterTileCollection::score() const {
	unsigned int result = 0;
	for (vector<LetterTile>::const_iterator i = _container.begin(); i < _container.end(); ++i) {
		result += i->score;
	}
	return result;
}

// Additional method sort method that is used to sort the LetterTileCollection
void LetterTileCollection::msort(){
        sort(_container.begin(), _container.end());
}

// Returns a pointer to a new LetterTile from the container (lab4)
LetterTile* LetterTileCollection::operator[](int position) const {
	return new LetterTile(_container[position]);
}

// This method takes a LetterTile and push it back into the _container (Lab4)
void LetterTileCollection::insert(LetterTile & lt) {
	_container.push_back(lt);
}

// This method takes a LetterTileCollection and push back the LetterTile in the position into the _container (Lab4)
void LetterTileCollection::insert(const LetterTileCollection & ltc, int position) {
	_container.push_back(ltc._container[position]);
}