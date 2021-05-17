//
// Created by Neron on 21/4/2021.
//
#include <string>
#include <cmath>
#include <iostream>


#ifndef TEST_HASHTABLE_H
#define TEST_HASHTABLE_H
using namespace std;

/*
 *  N O D E S !
 */
class Cell {
public:

    string word;                                      //The word that is stored
    int occurrences = 0;                              //Int containing the appearances of a word (set externally)
};

/*
 *  H A S H E S
 */
class hashTable {                                   //Implementation of chain hashing
private:
    long size = 256;                                //Size of the hash table
    Cell *table = new Cell[size];                   //Array of subarrays
    long occupied = 0;
    long expand_threshold = floor(sqrt(size));  //How many empty cells should be left before expanding the table

    void update_threshold(){
        expand_threshold = floor(sqrt(size));
    }

    long stringToHash(const string word, long max) const;            //Algorithm to convert strings into hash keys
    void expandAndRehash();
public:

    bool insertUnique(string word, int occurrences);
    bool insert(string word);     //Insert a word  and occurrence num into the table if it doesn't exist. Returns 1 if it was added.
    int search(string word);      //Find a word within the table and return it's occurrence number (0 if it doesn't exist)
    long getSize(){return occupied;}

};


#endif //TEST_HASHTABLE_H
