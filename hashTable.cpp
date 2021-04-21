//
// Created by Neron on 21/4/2021.
//

#include "hashTable.h"

Node::Node(string word, int occurences) {   // Constructor for the Node class
    this->word = word;
    this->occurences = occurences;
}

void list::add(string word, int occurences) {   //Node add algorithm; Finds the end of the Node chain and initializes
    if (first == nullptr){                      //a new node at the end. Also iterates the len variable
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
