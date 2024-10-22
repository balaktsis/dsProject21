//
// Created by Christos Balaktsis on 21/4/2021.
//

#include "UnorderedArray.h"
#include <string>
#include <algorithm>


UnorderedArray::UnorderedArray() {
    data = nullptr;
    num = nullptr;
    size = 0;
    current_size = 0;
	step = 5000;
}

void UnorderedArray::insert(const string &word) {           //Inserts a new word in the array, after checking its existence
    long pos;
    if (!Search_help(word,pos)) {
        insertUnique(word,1);
    }
    else {
        num[pos]++;
    }
}

void UnorderedArray::insertUnique(const string &word, int m) {
    if (data != nullptr && current_size == size) {
        string *new_data;
        int *new_num;

        new_data = new string[size+step];
        new_num = new int[size+step];

        copy(data,data+size, new_data);
        copy(num,num+size, new_num);

        delete[] data;
        delete[] num;
        data = new_data;
        num = new_num;
        current_size = size;
        size+=step;
        }
    else if(data == nullptr) {
        string *new_data;
        int *new_num;
        new_num = new int[step];
        new_data = new string[step];
        current_size = 0;
        size = step;
        delete[] data;
        data = new_data;
        delete[] num;
        num = new_num;
    }
    data[current_size] = word;
    num[current_size] = m;
    current_size++;
}

int UnorderedArray::search(const string &word) {
    if(size == 0) {
        return 0;
    }
    else {
        for(long i = 0; i <= current_size; i++) {
            if(data[i] == word) {
                return num[i];
            }
        }
        return 0;
    }
}

bool UnorderedArray::Search_help(const string &word, long &pos) {
    if(size == 0) {
        return false;
    }
    else {
        for(long i = 0; i <= current_size; i++) {
            if(data[i] == word) {
                pos = i;
                return true;
            }
        }
        return false;
    }
}

bool UnorderedArray::deleteWord(const string &word) {           //Deletes an existing word of the array or returns false
    long pos;                                                   //if word doesn't exist
    if(!Search_help(word,pos)) {                            //Checks the existence and returns position in array (if true)
        return false;
    }
    else {
        string *new_data;
        int *new_num;

        new_data = new string[size-1];
        new_num = new int[size-1];

        copy(num,num+pos,new_num);
        copy(data,data+pos, new_data);
        //Copying to new arrays (one-less-cell-sized) data[] and num[]

        for(long i = pos; i < size-1; i++) {
            new_num[i] = num[i+1];
            new_data[i] = data[i+1];
        }
        size--;
        delete[] data;
        delete[] num;
        data = new_data;                                            //Linking new arrays to the object pointers (data, num)
        num = new_num;

        return true;
    }
}

UnorderedArray::~UnorderedArray() {
    delete[] data;
}

long UnorderedArray::getSize() const {
    return current_size;
}

int UnorderedArray::getNum(long pos) const {
    return num[pos];
}
string UnorderedArray::getData(long pos) const {
    return data[pos];
}
