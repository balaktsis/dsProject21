//
// Created by Neron on 24/4/2021.
//

#include "orderedArray.h"
#include <string>



using namespace std;

orderedArray::orderedArray() {      //Initializing the array with null pointers and a size of zero
    table = nullptr;
    size = 0;
}

void orderedArray::swap(Cell &a, Cell &b) {
    Cell temp;
    temp = a;
    a = b;
    b = temp;
}



void orderedArray::quicksort(long start, long end) {        //Standard recursive quicksort implementation
    long i, j, pivot;                                       //With the pivot on the 1st element
    string tempWord;

    if (start < end) {
        pivot = start;
        i = start;
        j = end;

        while (i < j) {
            for (; table[i].word <= table[pivot].word && i < end; ++i) {}
            for (; table[j].word > table[pivot].word; --j) {}

            if (i < j) {
                swap(table[i], table[j]);
            }
        }

        swap(table[pivot], table[j]);

        quicksort(start, j - 1);
        quicksort(j + 1, end);

    }
}

void orderedArray::copyFromUnordered(string *newData, int *newNum, long arraySize) {    //Implement quicksort on a string array
    this->size = arraySize;                                                             //and keep it in relation to an int array
    this->table = new Cell[size];
    if (size == 1){
        this->table[0].word = newData[0];
        this->table[0].occurrences = newNum[0];
        return;
    }

    for (int i = 0; i < arraySize - 1; ++i) {                     //Copy two arrays passed by reference locally
        table[i].word = newData[i];
        table[i].occurrences = newNum[i];
    }

    quicksort(0, size - 1);

}

bool orderedArray::binSearch(const string &word, long &pos) {       //Implementation of binary search
    if (size == 0) {                                                //If it's empty, it returns false (not found)
        pos = 0;
        return false;
    }
    if (table[0].word == word){
        pos = 0;
        return true;
    }


    long begin = 0, end = size - 1;                         //Initializing the pointers to the front, middle and end.
    long mid = 0;

    while (begin <= end){                                   //Main loop, checking where the sought-after word is in

        mid = begin + (end-begin) / 2;

        if(table[mid].word == word){
            pos = mid;
            return true;
        }
        if (word > table[mid].word) {                               //relation to the mid pointer.
            begin = mid + 1;                                        //Depending on that, the array is divided.
        } else {
            end = mid - 1;
        }
    }

    pos = mid;                                                      //Returning the position of the word (by reference).
    return false;                                                   //Returning a bool value depending on if it's found.

}

void orderedArray::insert(const string &word) {                      //Insert single word into array/Increment if already in.

    if (size == 0) {                                                 //If the array is empty, initializing with one cell.
        size++;
        table = new Cell[size];
        table[0].word = word;
        table[0].occurrences = 1;
        return;
    }

    long pos;                                                 //Check if the word already exists in array.
    if (binSearch(word, pos)) {                            //If the search returns true, it's appearance num gets incremented.
        table[pos].occurrences += 1;
        return;
    }

    Cell *newTable = new Cell[size+1];
                                                                //Initializing a temporary 2nd array with n+1 cells
                                                                //Then all the cells up to where the new word should be placed
                                                                //are copied over. After that, the word gets inserted
                                                                //and the rest of the cells are copied over, 1 position after

    pos = 0;
    for (pos = 0; pos < size && table[pos].word < word; ++pos) {
        newTable[pos] = table[pos];
    }

    newTable[pos].word = word;
    newTable[pos].occurrences = 1;



    for (long i = pos + 1; i <= size; ++i) {
        newTable[i] = table[i-1];
    }

    size++;
    delete[] table;
    table = newTable;


}

void orderedArray::insertUnique(const string& word, const int occurrences) {    //Identical to insert, but takes a set
                                                                                //amount of occurrences, instead of
    if (size == 0) {                                                            //manually incrementing
        size++;
        table = new Cell[size];
        table[0].word = word;
        table[0].occurrences = occurrences;
        return;
    }

    long pos;
    if (binSearch(word, pos)) {  //If the word already exists, discard the operation
        return;
    }

    Cell *newTable = new Cell[size+1];

    pos = 0;
    for (pos = 0; pos < size && table[pos].word < word; ++pos) {
        newTable[pos] = table[pos];
    }

    newTable[pos].word = word;
    newTable[pos].occurrences = occurrences;



    for (long i = pos + 1; i <= size; ++i) {
        newTable[i] = table[i-1];
    }

    size++;
    delete[] table;
    table = newTable;
}

int orderedArray::search(const string& word) {       //Implementation of the binary search algo, but for public use.
    if (size == 0) {                                 //Returns the occurrences of a word (0 if none)
        return 0;
    }
    long pos;
    return binSearch(word, pos) ? table[pos].occurrences : 0;
}

void orderedArray::remove(const string &word) {         //The insert algorithm in reverse.
                                                        //Check if the word exists, then reduce the array size by one
                                                        //and slide the cells after the removed word one position down.
    long pos;
    if (!binSearch(word, pos)) {  //If the word doesn't exist, discard the operation.
        return;
    }

    Cell *newTable = new Cell[size-1];

    for (long i = 0; i < pos; ++i) {
        newTable[i] = table[i];
    }

    for (long i = pos; i < size - 1; ++i) {
        newTable[i] = table[i + 1];
    }
    size--;

    delete[] table;
    table = newTable;

}

long orderedArray::getSize() const {
    return size;
}

