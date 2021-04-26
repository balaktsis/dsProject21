//
// Created by Neron on 24/4/2021.
//

#include "orderedArray.h"
#include <string>

using namespace std;
orderedArray::orderedArray() {
    data = nullptr;
    num = nullptr;
    size = 0;
}

void orderedArray::copyFromUnordered(string *newData, int *newNum, long arraySize) {
    this->data = newData;
    this->num = newNum;
    size = arraySize;

    //TODO:Quicksort

}

bool orderedArray::binSearch(const string &word, long &pos) {
    long begin = 0, end = size-1;
    long mid = (begin+end)/2;

    while (mid != end || mid != begin){
        if (word > data[mid]){
            begin = mid;
        } else {
            end = mid;
        }
        mid = (begin+end)/2;
    }

    pos = mid;
    return data[mid] == word;

}

void orderedArray::insert(const string& word) {
    long pos;
    if (binSearch(word, pos)){
        num[pos] += 1;
        return;
    }

    string *newData = new string[size+1];
    int *newNum = new int[size+1];
    copy(&data[0],&data[pos] , newData);
    copy(&num[0],&num[pos] , newNum);
    newData[pos+1] = word;
    newNum[pos+1] = 1;
    for (int i = pos+1; i < size; ++i) {
        newData[i+1] = data[i];
        newNum[i+1] = num[i];
    }
    size++;
    data = newData;
    num = newNum;
    delete[] newNum;
    delete[] newData;

}

void orderedArray::insertUnique(const string word, const int occurrences) {
    long pos;
    if (binSearch(word, pos)){  //If the word already exists, discard the operation
        return;
    }

    string *newData = new string[size+1];
    int *newNum = new int[size+1];
    copy(&data[0],&data[pos] , newData);
    copy(&num[0],&num[pos] , newNum);
    newData[pos+1] = word;
    newNum[pos+1] = occurrences;
    for (int i = pos+1; i < size; ++i) {
        newData[i+1] = data[i];
        newNum[i+1] = num[i];
    }
    size++;
    data = newData;
    num = newNum;
    delete[] newNum;
    delete[] newData;
}

int orderedArray::search(const string word) {
    long pos;
    return binSearch(word, pos) ? num[pos] : 0;
}

void orderedArray::remove(const string word) {
    long pos;
    if (!binSearch(word, pos)){  //If the word already exists, discard the operation
        return;
    }

    string *newData = new string[size-1];
    int *newNum = new int[size-1];
    copy(&data[0],&data[pos-1] , newData);
    copy(&num[0],&num[pos-1] , newNum);
    for (int i = pos; i < size; ++i) {
        newData[i] = data[i+1];
        newNum[i] = num[i+1];
    }
    size--;
    data = newData;
    num = newNum;
    delete[] newNum;
    delete[] newData;
}

int orderedArray::getSize() {
    return size;
}
