//
// Created by Neron on 21/4/2021.
//

#include "hashTable.h"
using namespace std;



/*
 *  H A S H E S
 *  hash-ta la vista ;)
 */

long hashTable::stringToHash(const string word, long max) const{            //Implementation of a polynomial hash function

    int prime = 31, seed = 1;
    long m = max;
    long hash_val = 0;

    for (char i : word) {                                                   //Iterating through the chars in the word
        hash_val = (hash_val + (i + 1 - 'a') * seed) % m;                   //and doing math with their decimal value in ASCII
        seed = (seed * prime) % m;
    }
    return hash_val;
}

bool hashTable::insert(const string word) {                                   //Insert algorithm for the Hash table
    long key = stringToHash(word, size);                                //Takes a string and generates it's key

    for (long i = key; i < size; ++i) {                                        //Linear search starting from the key.
                                                                              //If the word is found, it's occurrence value
        if (table[i].occurrences && table[i].word == word){                   //is incremented and the operation ends
            table[i].occurrences += 1;                                        //returning 'false' as the word wasn't inserted
            return false;
        } else if (table[i].occurrences == 0){                                //If the word is not found, it gets inserted in the
            table[i].word = word;                                             //next unoccupied cell
            table[i].occurrences = 1;
            occupied++;
            break;
        }

        if (i == size-1){                                                     //If the end of the table is reached, we loop back to the front
            i = -1;     //Using value -1 because it's incremented automatically by the for loop
        }
                                                                                //In theory a state with no exit condition
                                                                                //exists, but it's impossible to reach, as there's
                                                                                //always going to be empty cells within the
                                                                                //array, for it to reach an exit.
    }



    if (size - expand_threshold == occupied){                                   //If enough of the table is filled
                                                                                //the expand function is called.
        expandAndRehash();
    }

    return true;

}


bool hashTable::insertUnique(string word, int occurrences) {                    //Same functionality and structure as simple insert
    long key = stringToHash(word, size);                                  //But the word occurrences are passed as a parameter

    for (long i = key; i < size; ++i) {

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
            i = -1;     //Using value -1 because it's incremented automatically by the for loop
        }
    }



    if (size - expand_threshold == occupied){
        expandAndRehash();
    }

    return true;
}



int hashTable::search(const string word) {          //Search algorithm, with a word as a parameter and returns it's occurrences (0 if none)
    long key = stringToHash(word, size);      //Starts off by generating a key from the word.

    for (long i = key; i < size; ++i) {             //Then a linear search begins from the key and linearly parses cells
                                                    //Until either the word is found, or an empty cell is reached (not found)

        if (table[i].word == word && table[i].occurrences){
            return table[i].occurrences;
        } else if (table[i].occurrences == 0){
            return 0;
        }
        if (i == size-1){
            i = -1;
//            overflow = 1;
        }


    }
    return 0;
}

void hashTable::expandAndRehash() {         //Table expansion algorithm
                                            //Doubling the array size at each invocation
    long oldSize = size;
    size = size*2;                          //Starts off by creating a duplicate of the array
    update_threshold();                     //erasing the main one, allocating double the memory to it
    occupied = 0;                           //and inserting all the words from the duplicate back to it (using an updated hashing algorithm)
                                            //that yields larger keys

    Cell *oldTable = table;
    table = new Cell[size];

    for (long i = 0; i < oldSize; ++i) {
        if (oldTable[i].occurrences == 0){       //Skip vacant cells
            continue;
        }

        insertUnique(oldTable[i].word, oldTable[i].occurrences);

    }

    delete[] oldTable;

}


