//
// Created by Neron on 21/4/2021.
//
#include <string>
#ifndef TEST_HASHTABLE_H
#define TEST_HASHTABLE_H
using namespace std;

class Node {
public:

    Node(string word, int occurences);
    string word;
    int occurences;
    Node* next = nullptr;
};


class list{
private:
    Node *first = nullptr;
public:
    int len = 0;
    void add(string word, int occurences);
    int find(string); //Find a word within the list and returns it's occurence number (0 if it doesn't exist)

};

class hashTable { //Implementation of chain hashing
private:

public:


};


#endif //TEST_HASHTABLE_H
