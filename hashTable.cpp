//
// Created by Neron on 21/4/2021.
//

#include "hashTable.h"

/*
 *  N O D E S !
 */

Node::Node(string word, int occurences) {   // Constructor for the Node class
    this->word = word;
    this->occurences = occurences;
}

/*
 *  L I S T !
 */



void list::insert(string word, int occurences) {   //Node insertion algorithm; Finds the end of the Node chain and
    if (first == nullptr){                         //initializes a new node at the end. Also iterates the len variable
        first = new Node(word, occurences);
    }
    else {
        Node *accessedNode = first;
        for (int i = 0; i < len-1; ++i) {
            accessedNode = accessedNode->next;
        }
        accessedNode->next = new Node(word, occurences);
    }
    len++;
}

int list::find(string word) {                //Iterate through all the Nodes in the list to find a certain string.
    Node *accessedNode = first;              //If the string isn't found it'll return 0.

    while (accessedNode!= nullptr) {
        if (accessedNode->word == word){
            return accessedNode->occurences;
        }
        accessedNode = accessedNode->next;
    }

    return 0;                                //This point will be reached only if the word isn't found.
}

/*
 *  H A S H E S
 *  hash-ta la vista ;)
 */

hashTable::hashTable() {
    this->table = new list[size];
}

hashTable::hashTable(int size) {
    this->size = size;
    this->table = new list[size];
}

int hashTable::stringToHash(string word) {      //Implementation of a polynomial hash function


    int prime = 31, m = size, seed = 1;
    int hash_val = 0;

    for (char i : word) {                   //Iterating through the chars in the word
        hash_val = (hash_val + (i + 1 - 'a') * seed) % m;
        seed = (seed * prime) % m;
    }
    return hash_val;
}

int hashTable::find(string word) {
    int key = stringToHash(word);
    return table[key].len ? table[key].find(word) : 0;
}

void hashTable::insert(string word, int occurences) {
    if (find(word)){                    //Check if the word exists already
        return;
    }
    int key = stringToHash(word);       //If the code reaches here, the word doesn't exist, so a key is generated
    table[key].insert(word, occurences);//and inserted in the appropriate spot on the table
}
