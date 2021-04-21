//
// Created by Christos Balaktsis on 21/4/2021.
//

#ifndef UNORDEREDARRAY_H
#define UNORDEREDARRAY_H
#include <string>
using namespace std;

class UnorderedArray {
protected:
    string *data;       //array of strings
    int *num;           //number of appearances of each string/word
    int size;           //size of array
    bool Search_help(const string &); //Checks the existence of a word in array; true := word exists
public:
    UnorderedArray();
    void Insert(const string &);                    //Inserts a NEW word in array (checks for existed ones)
    bool Search(const string &, double &, int &);   //Searches for a given word and returns (by ref.) time needed and number of appearances; true := word exists
};
#endif //UNORDEREDARRAY_H
