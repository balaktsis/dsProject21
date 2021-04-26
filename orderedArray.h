//
// Created by Neron on 24/4/2021.
//

#ifndef TEST_ORDEREDARRAY_H
#define TEST_ORDEREDARRAY_H
#include <string>

using namespace std;
class orderedArray {
private:
    string *data;               //Array storing the words (kept in relation to num)
    int *num;                   //Array storing the occurrences of words.
    long size;                  //Size of the array
public:
    orderedArray();
    void copyFromUnordered(string *newData, int *newNum);           //Copy a non sorted array and sort it.
    void insert(const string word);                                 //Get a word and insert it in the correct order/increment it's appearance number
    void insertUnique(const string word, const int occurrences);    //Get a word and occurrence number and place it in the correct spot
    int search(const string word);                                  //Search for a word and return it's occurrences (0 for none)
    bool remove(const string word);                                 //Remove word from the array and readjust the order
    int getSize();                                                  //Returns the size of the array.



};


#endif //TEST_ORDEREDARRAY_H
