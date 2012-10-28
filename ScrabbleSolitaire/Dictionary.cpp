// Dictionary.h
// Joao Felipe Nicolaci Pimentel <joaofelipenp@gmail.com>
// Defines the Dictionary methods

#include "stdafx.h"
#include "Dictionary.h"
#include "Consts.h"
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

// Default constructor in Dictionary that initializes a empty container
Dictionary::Dictionary () 
	: _container() { }

// Constructor that takes a file name and reads it into container
Dictionary::Dictionary (const string & filename) 
	: _container() { 
	if (add(filename) != 0) {
		_container = set<string>();
	}
}

// Reads a dictionary file to the container
// Returns INPUT_FILE_ERROR if it can't open file
int Dictionary::add(const string & filename) {
	ifstream ifs(filename.c_str());
	if (ifs.is_open()) {
		while (!ifs.eof()) {
			string line;
			getline(ifs, line);
			if (line.find("//") == line.npos) {
				istringstream iss(line);
				while (!iss.eof()) {
					string word;
					iss >> word;
					if (!word.empty()) {
						_container.insert(word);
					}
				}
			}
		}
		ifs.close();
	} else {
		return INPUT_FILE_ERROR;
	}
	return 0;
	
}

// Returns the number of elements in container
int Dictionary::size() const {
	return _container.size();
}

// Prints all _container contents to stream
void Dictionary::print(ostream & stream) const {
	for (set<string>::const_iterator i = _container.begin(); i != _container.end(); ++i) {
		stream << *i << endl;
	}
}

// Finds a word in the Dictionary
bool Dictionary::find(const string & word) const {
	set<string>::const_iterator i = std::find(_container.begin(), _container.end(), word);
	return (i != _container.end());
}
