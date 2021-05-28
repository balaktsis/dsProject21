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

#ifndef TEST_MAINFUNCTIONS_H
#define TEST_MAINFUNCTIONS_H

using namespace std;
using namespace std::chrono;


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
    string *wordsHolder;
    int *numsHolder;

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
//            if (count%25000000 == 0){ printf("%ld words read...\n"), count/25000000;}
//            cout<<word<<endl;
//            if (HashTable.insert(word)) {                //Inserting words into the hashtable; returns true if the word is unique.
//                                                         //If it's not unique, it increments it's internal occurrence counter.
//                uniqueCount++;
//                cout<<word<<endl;
//                unorderedArray.insertUnique(word, 0);    //Initializing the unordered array, just with the unique words.
//            }                                              //We'll use it as a lookup table later. So occurrences are 0.
            HashTable.insert(word);
            BinaryTree.insert(word);
            unorderedArray.insert(word);
            OrderedArray.insert(word);
            AvlTree.insert(word);

        }
        ifs.close();

        uniqueCount = HashTable.getSize();

//        wordsHolder = new string[uniqueCount];
//        numsHolder = new int[uniqueCount];

//        for (long i = 0; i < uniqueCount; ++i) {
//            wordsHolder[i] = unorderedArray.getData(i);
//            numsHolder[i] = HashTable.search(wordsHolder[i]);
//        }

//        OrderedArray.copyFromUnordered(wordsHolder, numsHolder, uniqueCount);

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

void timeQSearches(int searchCount, UnorderedArray &unorderedArray, hashTable &HashTable, orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree){
    string words[searchCount];
    int value;
    srand(searchCount);
    for (int i = 0; i < searchCount; ++i) {         //Filling a Q-sized array with randomly chosen words
        value = rand() % searchCount;
        words[i] = unorderedArray.getData(value);
//        words[i] = unorderedArray.getData(i);
    }

    //Initializing timing
    auto begin = high_resolution_clock::now(), end = high_resolution_clock::now() ;
    duration<double, milli> elapsed = end - begin;
    long count;

    /*
     * Calculating the time to search all Q randomly picked words in each structure.
     * count    : Counts the words returned, useful in order to validate the results
     * begin    : Timestamp at the start of the search
     * for loop : Iterating through every word in words (initialized earlier) and doing a search for it in each
     * structure, increasing count by the return value.
     * end      : Timestamp at the end of the search
     * elapsed  : Time between end and begin in milliseconds.
     */

    //Timing for the Unordered Array
    count = 0;
    begin = high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {count += unorderedArray.search(words[i]);}
    end = high_resolution_clock::now();
    elapsed = end - begin;
    cout<<"Searching "<<searchCount<<" words in the Unordered Array yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;

    //Timing for the Ordered Array
    count = 0;
    begin = high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {count += OrderedArray.search(words[i]);}
    end = high_resolution_clock::now();
    elapsed = end - begin;
    cout<<"Searching "<<searchCount<<" words in the Ordered Array yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;

    //Timing for the Binary Search Tree
    count = 0;
    begin = high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {count += BinaryTree.search(words[i]);}
    end = high_resolution_clock::now();
    elapsed = end - begin;
    cout<<"Searching "<<searchCount<<" words in the Binary Search Tree yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;


    //Timing for the AVL tree
    count = 0;
    begin = high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {count += AvlTree.search(words[i]);}
    end = high_resolution_clock::now();
    elapsed = end - begin;
    cout<<"Searching "<<searchCount<<" words in the AVL tree yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;

    //Timing for the Hash Table
    count = 0;
    begin = high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {count += HashTable.search(words[i]);}
    end = high_resolution_clock::now();
    elapsed = end - begin;
    cout<<"Searching "<<searchCount<<" words in the Hash Table yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;

}




#endif //TEST_MAINFUNCTIONS_H
