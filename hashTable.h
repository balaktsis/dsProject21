//
// Created by Neron on 21/4/2021.
//
#include <string>

#ifndef TEST_HASHTABLE_H
#define TEST_HASHTABLE_H
using namespace std;

/*
 *  N O D E S !
 */
class Node {
public:
    Node(string word, int occurrences);  //Non-empty constructor that initializes the word & occurrences fields.

    string word;                  //The word that is stored
    int occurrences;               //Int containing the appearances of a word (set externally)
    Node *next = nullptr;         //Pointer to next node in the list. Nullptr when last
};

/*
 *  L I S T !
 */
class list {
private:
    Node *first = nullptr;        //Pointer to first node in the list (initialized as nullptr)
public:
    int len = 0;                  //Size of the list

    void insertUnique(const string& word, int occurrences);   //insert word and occurrence num into list (if doesn't exist)
    bool insert(const string& word);     //insert word into list (if doesn't exist) and iterate it's occurrences. Returns 1 if it was added.
    int search(const string& word);      //Find a word within the list and return it's occurrence number (0 if it doesn't exist)
};

/*
 *  H A S H E S
 */
class hashTable {                 //Implementation of chain hashing
private:
    long size = 100;               //Size of the hash table
    list *table;                  //Array of lists

    int stringToHash(const string& word) const;//Algorithm to convert strings into hash keys
public:
    hashTable();                  //Constructor for the hash table with default size
    hashTable(long size);         //Constructor for the hash table with custom size

    void insertUnique(const string& word, int occurrences);   //Insert a word  and occurrence num into the table if it doesn't exist
    bool insert(const string& word);     //Insert a word  and occurrence num into the table if it doesn't exist. Returns 1 if it was added.
    int search(const string& word);      //Find a word within the table and return it's occurrence number (0 if it doesn't exist)
};


#endif //TEST_HASHTABLE_H
