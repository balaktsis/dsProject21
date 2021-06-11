//
// Created by Christos Balaktsis on 21/4/2021.
//

#ifndef UNORDEREDARRAY_H
#define UNORDEREDARRAY_H
#include <string>
using namespace std;

class UnorderedArray {
protected:
    int step;
    string *data;                                   //array of strings
    int *num;                                       //number of appearances of each string/word
    long size;                                      //size of array
    long current_size;                              //used sized of array-1
    bool Search_help(const string &, long &);       //Checks the existence of a word in array and returns position in array (if true)
public:
    UnorderedArray();                               //Unordered Array constructor
    ~UnorderedArray();                              //Unordered Array destructor
    void insert(const string &);                    //Inserts a NEW word in array (checks for existed ones)
    void insertUnique(const string &, int);         //Inserts a word in array (takes word and number of appearances).
    int search(const string &);      				//Searches for a given word and returns (by ref.) position and number of appearances; true := word exists
    bool deleteWord(const string &);                //Deletes a word of the array (if data deletion is completed, returns true)
    long getSize() const;                           //Returns the size of the two arrays
    int getNum(long) const;                         //Returns num[pos]
    string getData(long) const;                     //Returns data[pos]
};
#endif //UNORDEREDARRAY_H
