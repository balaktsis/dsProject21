//
// Created by Neron on 21/4/2021.
//

#include "hashTable.h"
#include <cmath>
using namespace std;



/*
 *  H A S H E S
 *  hash-ta la vista ;)
 */

long hashTable::stringToHash(const string word, long max) const{         //Implementation of a polynomial hash function

    int prime = 31, seed = 1;
    long m = max;
    long hash_val = 0;

    for (char i : word) {                                       //Iterating through the chars in the word
        hash_val = (hash_val + (i + 1 - 'a') * seed) % m;
        seed = (seed * prime) % m;
    }
    return hash_val;
}

bool hashTable::insert(const string word) {
    long key = stringToHash(word, size);

    for (int i = key; i < size; ++i) {
        D:
        if (table[i].occurrences && table[i].word == word){
            table[i].occurrences += 1;
            return false;
        } else if (table[i].occurrences == 0){
            table[i].word = word;
            table[i].occurrences = 1;
            occupied++;
            break;
        }

        if (i == size-1){
            i = 0;
            goto D;
        }
    }



    if (size - expand_threshold == occupied){
        expandAndRehash();
    }

    return true;

}


bool hashTable::insertUnique(string word, int occurrences) {
    long key = stringToHash(word, size);

    for (int i = key; i < size; ++i) {
        C:
        if (table[i].occurrences && table[i].word == word){
            table[i].occurrences = occurrences;
            return false;
        } else if (table[i].occurrences == 0){
            table[i].word = word;
            table[i].occurrences = occurrences;
            occupied++;
            break;
        }

        if (i == size-1){
            i = 0;
            goto C;
        }
    }



    if (size - expand_threshold == occupied){
        expandAndRehash();
    }

    return true;
}



int hashTable::search(const string word) {
    long key = stringToHash(word, size);
    char overflow = 0;

    for (int i = key; i < size; ++i) {
        B:
        if (table[i].word == word && table[i].occurrences){
            return table[i].occurrences;
        } else if (table[i].occurrences == 0){
            return 0;
        }
        if (i == size-1 && !overflow){
            i = 0;
            overflow = 1;
            goto B;
        }
        if (overflow && i == key){         //Once the linear search completes a loop through the array, without finding
            return 0;                       //the key, 0 (not found) is returned.
        }

    }
    return 0;
}

void hashTable::expandAndRehash() {

    long oldSize = size;
    size = size*2;
    update_threshold();
    occupied = 0;


    Cell *oldTable = table;
    table = new Cell[size];

    for (int i = 0; i < oldSize; ++i) {
        if (oldTable[i].occurrences == 0){       //Skip vacant cells
            continue;
        }

        insertUnique(oldTable[i].word, oldTable[i].occurrences);

    }

    delete[] oldTable;

}


