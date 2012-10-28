// WordCollection.cpp
// Kaichen Zhang <zkcwustl@gmail.com>
// lab 3
// represent the possible valid rearrangements of a collection of letter tiles that make up words that are found in a dictionary

#include "stdafx.h"
#include "WordCollection.h"
#include <algorithm>

WordCollection::WordCollection(const LetterTileCollection &ltc, const Dictionary &d){
    LetterTileCollection mtc(ltc);
    mtc.msort();
    LetterTileCollection ntc;
    do{
        ntc = mtc;
        LetterTileCollection otc;
        while (ntc.size() > 0){
            otc.move(ntc, 1);
            otc.msort();
            if (d.find(otc.as_string()) && s_.find(otc) == s_.end()) {
				s_.insert(otc);
			}
        }
    }while (mtc.permute());
}

void WordCollection::print(ostream &o)const{
    for (set<LetterTileCollection>::const_iterator i = s_.begin(); i != s_.end(); ++i) {
	    o << (*i).score() << (*i).as_string() << endl;
	}
}