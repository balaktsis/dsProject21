//
// Created by Christos Balaktsis on 21/4/2021.
//

#ifndef UNORDEREDARRAY_H
#define UNORDEREDARRAY_H
#include <string>
using namespace std;

class UnorderedArray {
protected:
    string *data;   //array of strings
    int *num;       //number of appearances of each string/word
    int size;       //size of array
public:
    UnorderedArray();
    void Insert(const string &);
    bool Search(const string &, double &, int &);   //Searches for a given word and returns (by ref.) time needed and number of appearances

};
#endif //UNORDEREDARRAY_H
