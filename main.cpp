#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>

#include "UnorderedArray.h"
#include "hashTable.h"
#include "orderedArray.h"
#include "BSTree.h"
#include "AVLtree.h"


using namespace std;
using namespace std::chrono;

string wordStrip(const string &word);
long initStructures(const string &filename, UnorderedArray &unorderedArray, hashTable &HashTable, orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree);
void timeQSearches(int searchCount, UnorderedArray &unorderedArray, hashTable &HashTable, orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree);

template<typename searchable>
void calcSearch(searchable structure, int searchCount, string *words, string arrName);


int main() {

    string filename = "../medium-file.txt";   //Name of the input file ('../' is needed for the project to compile on CLion)

    //Declaring variables for each data structure (Uninitialized)
    hashTable HashTable;
    UnorderedArray unorderedArray;
    orderedArray OrderedArray;
    BSTree BinaryTree;
    AVLTree AvlTree;



    printf("Filling up the arrays...\n");

    //Fill up the data structures from the file.
    initStructures(filename, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);


    //Search benchmark (first parameter being the random word count - Q)
    timeQSearches(1000, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);

    printf("Hi!");
    return 0;
}


string wordStrip(const string &word) {
    string temp;                            //Initialize empty string
    for (char i : word) {                   //Iterate through all chars in the word
        if ('A' <= i && i <= 'Z') {              //Make char lowercase
            i += 'a' - 'A';
        } else if (!('a' <= i && i <= 'z')) {    //Discard non alphabetical chars
            continue;
        }
        temp += i;                          //Add valid characters (lowercase alphabetic) to the temp string
    }
    return temp;
}

long initStructures(const string &filename, UnorderedArray &unorderedArray, hashTable &HashTable, orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree) {
    long count = 0;
    long uniqueCount = 0;
    string word;

    // Timing
    auto begin = high_resolution_clock::now(), end = high_resolution_clock::now() ;
    duration<double> elapsed = end - begin;


    ifstream ifs;
    ifs.open(filename);
    if (ifs.is_open()) {
        cout << "File open ok" << endl;
        while (ifs >> word) {
            word = wordStrip(word);                       //Strips word of any non alphabetic characters and lowercases it.
            // Eg. "1.Your's" becomes "yours"
            if (word.empty() || (0 <= word[0] && word[0] <= 32)) {
                continue;
            }
            count++;
            HashTable.insert(word);
            BinaryTree.insert(word);
            unorderedArray.insert(word);
            OrderedArray.insert(word);
            AvlTree.insert(word);

        }
        ifs.close();
        uniqueCount = HashTable.getSize();

        end = high_resolution_clock::now();
        elapsed = end - begin;
        cout<<"Filled up the structures in: "<<elapsed.count()<<"s"<<endl;

        printf("Unique words: %ld.\n", uniqueCount);
        printf("Total words: %ld.\n", count);

        cout<<"Size of Unordered: "<<unorderedArray.getSize()<<endl;
        cout<<"Size of Ordered: "<<OrderedArray.getSize()<<endl;
        cout<<"Size of Hash Table: "<<HashTable.getSize()<<endl;

    } else
        cout << "File error" << endl;

    return count;
}

template<typename searchable>
void calcSearch(searchable structure, int searchCount, string *words, string arrName){


    /*
     * Calculating the time to search all Q randomly picked words in each structure.
     * count    : Counts the words returned, useful in order to validate the results
     * begin    : Timestamp at the start of the search
     * for loop : Iterating through every word in words (initialized earlier) and doing a search for it in each
     * structure, increasing count by the return value.
     * end      : Timestamp at the end of the search
     * elapsed  : Time between end and begin in milliseconds.
     */

    long count = 0;
    auto begin = high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {count += structure.search(words[i]);}
    auto end = high_resolution_clock::now();
    duration<double, milli> elapsed = end - begin;
    cout<<"Searching "<<searchCount<<" words in "<<arrName<<" yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;
}



void timeQSearches(int searchCount, UnorderedArray &unorderedArray, hashTable &HashTable, orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree){
    string words[searchCount];
    int value;
    srand(searchCount);

    for (int i = 0; i < searchCount; ++i) {         //Filling a Q-sized array with randomly chosen words
        value = rand() % searchCount;
        words[i] = unorderedArray.getData(value);
    }

    //Timing for the Unordered Array
    calcSearch(unorderedArray, searchCount, words, "Unordered Array");

    //Timing for the Ordered Array
    calcSearch(OrderedArray, searchCount, words, "Ordered Array");

    //Timing for the Binary Search Tree
    calcSearch(BinaryTree, searchCount, words, "Binary Search Tree");

    //Timing for the AVL tree
    calcSearch(AvlTree, searchCount, words, "AVL Tree");

    //Timing for the Hash Table
    calcSearch(HashTable, searchCount, words, "Hash Table");

}