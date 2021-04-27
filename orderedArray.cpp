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
    if (size == 0){
        pos = 0;
        return false;
    }


    long begin = 0, end = size-1;
    long mid = (begin+end)/2;

    while (begin <= mid){
        if (word > data[mid]){
            begin = mid+1;
        } else if (data[mid] == word){
            pos = mid;
            return true;
        }
        else {
            end = mid-1;
        }
        mid = (begin+end)/2;
    }

    pos = mid;
    return data[mid] == word;

}

void orderedArray::insert(const string& word) {

    if (size == 0){
        size++;
        data = new string[size];
        num = new int[size];
        data[0] = word;
        num[0] = 1;
        return;
    }

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
    delete[] data;
    data = newData;
    delete[] num;
    num = newNum;

}

void orderedArray::insertUnique(const string word, const int occurrences) {

    if (size == 0){
        size++;
        data = new string[size];
        num = new int[size];
        data[0] = word;
        num[0] = occurrences;
        return;
    }

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
    delete[] data;
    data = newData;
    delete[] num;
    num = newNum;
}

int orderedArray::search(const string word) {
    if (size == 0){
        return 0;
    }
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
