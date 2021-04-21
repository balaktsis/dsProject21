//
// Created by Christos Balaktsis on 21/4/2021.
//

#include "UnorderedArray.h"
#include <string>
#include <chrono>

UnorderedArray::UnorderedArray() {
    data = nullptr;
    num = nullptr;
    size = 0;
}

void UnorderedArray::Insert(const string &word) {           //Inserts a new word in the array, after checking its existence
    int pos;
    if (!Search_help(word,pos)) {
        size++;                                             //Updates size of array and reallocates its content to an extended array
        if (data != nullptr) {
            string *new_data;
            int *new_num;

            new_data = new string[size];
            new_num = new int[size];

            for (int i = 0; i < size - 1; i++) {
                new_data[i] = data[i];
                new_num[i] = num[i];
            }
            delete[] data;
            delete[] num;
            data = new_data;
            num = new_num;
        }
        else {
            string *new_data;
            new_data = new string[size];
            delete[] data;
            data = new_data;
            int *new_num;
            new_num = new int[size];
            delete[] num;
            num = new_num;
        }
        data[size - 1] = word;
        num[size - 1] = 1;
    }
    else {
        num[pos]++;
    }
}

bool UnorderedArray::Search(const string &word, int &pos, int &num) {
    if(size == 0) {
        return false;
    }
    else {
        for(int i = 0; i < size; i++) {
            if(data[i] == word) {
                pos = i;
                num = this->num[i];
                return true;
            }
        }
        return false;
    }
}

bool UnorderedArray::Search_help(const string &word, int &pos) {
    int n;
    return Search(word,pos,n);
}

bool UnorderedArray::Delete(const string &word) {                   //Deletes an existing word of the array or returns false
    int pos;                                                        //if word doesn't exist
    if(!Search_help(word,pos)) {                                 //Checks the existence and returns position in array (if true)
        return false;
    }
    else {
        string *new_data;
        int *new_num;

        new_data = new string[size-1];
        new_num = new int[size-1];
                                                                    //Copying to new arrays (one-less-cell-sized) data[] and num[]
        for(int i = 0; i<pos; i++) {
            new_data[i] = data[i];
            new_num[i] = num[i];
        }

        for(int i = pos; i < size-1; i++) {
            new_data[i] = data[i+1];
            new_num[i] = num[i+1];
        }
        size--;
        delete[] data;
        delete[] num;
        data = new_data;                                            //Linking new arrays to the object pointers (data, num)
        num = new_num;

        return true;
    }
}
