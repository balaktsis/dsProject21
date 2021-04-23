//
// Created by Christos Balaktsis on 21/4/2021.
//

#include "UnorderedArray.h"
#include <string>
#include <cstring>

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

            memcpy(new_num,num,(size-1)*sizeof(int));
            for (int i = 0; i < size - 1; i++) {
                new_data[i] = data[i];
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

void UnorderedArray::InsertUnique(const string &word, int m) {
    size++;
    if (data != nullptr) {
        string *new_data;
        int *new_num;

        new_data = new string[size];
        new_num = new int[size];

        memcpy(new_num,num,(size-1)*sizeof(int));
        for (int i = 0; i < size - 1; i++) {
             new_data[i] = data[i];
         }
        delete[] data;
        delete[] num;
        data = new_data;
        num = new_num;
    }
    else {
        string *new_data;
        int *new_num;
        new_num = new int[size];
        new_data = new string[size];

        delete[] data;
        data = new_data;
        delete[] num;
        num = new_num;
    }
    data[size - 1] = word;
    num[size - 1] = m;
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


        memcpy(new_num,num,pos*sizeof(int));
                                                                   //Copying to new arrays (one-less-cell-sized) data[] and num[]
        for(int i = 0; i<pos; i++) {
            new_data[i] = data[i];
        }

        memcpy((new_num+(pos)*sizeof(int)),(num+(pos+1)*sizeof(int)),(size-1)*sizeof(int));
        for(int i = pos; i < size-1; i++) {
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

int UnorderedArray::getSize() const {
    return size;
}

int UnorderedArray::getNum(int pos) const {
    return num[pos];
}
string UnorderedArray::getData(int pos) const {
    return data[pos];
}