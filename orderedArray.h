//
// Created by Neron on 24/4/2021.
//

#ifndef TEST_ORDEREDARRAY_H
#define TEST_ORDEREDARRAY_H
#include <string>

using namespace std;


using namespace std;
class orderedArray {
private:

    class Cell {
    public:

        string word;                                      //The word that is stored
        int occurrences = 0;                              //Int containing the appearances of a word (set externally)
    };

    Cell *table;

    long size;                  //Size of the array.
    bool binSearch(const string &word, long &pos);   //Binary search to be used internally.
    void quicksort(long start, long end);
    void swap(Cell &a, Cell &b);
public:
    orderedArray();
    void copyFromUnordered(string *newData, int *newNum, long arraySize);           //Copy a non sorted array and sort it.
    void insert(const string& word);                                //Get a word and insert it in the correct order/increment it's appearance number.
    void insertUnique(const string& word, int occurrences);    //Get a word and occurrence number and place it in the correct spot.
    int search(const string& word);                                  //Search for a word and return it's occurrences (0 for none).
    void remove(const string& word);                                 //Remove word from the array and readjust the order.
    long getSize() const;                                                  //Returns the size of the array.
    void printTable(){
        for (int i = 0; i < size; ++i) {
            cout<<table[i].word<<" - "<<table[i].occurrences<<endl;
        }
    }



};


#endif //TEST_ORDEREDARRAY_H
