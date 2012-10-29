// WordCollection.h
// Kaichen Zhang <zkcwustl@gmail.com>
// lab 3
// definitions for the WordCollection

#ifndef WORDCOLLECTION_H
#define WORDCOLLECTION_H
#include <set>
#include "LetterTileCollection.h"
#include "Dictionary.h"

class WordCollection {
private:
        vector<LetterTileCollection> s_;
        WordCollection(const WordCollection &);
        WordCollection & operator=(const WordCollection &);

public:
        WordCollection(const LetterTileCollection &, const Dictionary &);
		//compiler supplied destructor is sufficient because there is no dynamic memory allocation
        void print(ostream & = cout)const;
};

#endif	