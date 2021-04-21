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
    void insert(string word, int occurences);
    int find(string);           //Find a word within the list and return it's occurence number (0 if it doesn't exist)

    /*void delete(string word) - Not necessary, since hashTable doesn't use it.*/
};

class hashTable {               //Implementation of chain hashing
private:
    int size = 100;
    list *table;
//    void empty();               //Called only by constructors to initialize all points with nullptr
    int stringToHash(string word);  //Algorithm to convert strings into hash keys

public:
    hashTable();                //Constructor for the hash table with default size
    hashTable(int size);        //Constructor for the hash table with custom size


    void insert(string word, int occurences);
    int find(string word);      //Find a word within the table and return it's occurence number (0 if it doesn't exist)
};


#endif //TEST_HASHTABLE_H
