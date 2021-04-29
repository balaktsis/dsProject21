#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>

#include "UnorderedArray.h"
#include "hashTable.h"
#include "orderedArray.h"
#include "BSTree.h"

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

long initStructures(const string &filename, UnorderedArray &unorderedArray, hashTable &HashTable, orderedArray &OrderedArray, BSTree &BinaryTree) {
    long count = 0;
    long uniqueCount = 0;
    string word;
    string *wordsHolder;
    int *numsHolder;

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
            if (HashTable.insert(word)) {           //Inserting words into the hashtable; returns true if the word is unique.
                                                         //If it's not unique, it increments it's internal occurrence counter.
                uniqueCount++;
                unorderedArray.insertUnique(word, 0);    //Initializing the unordered array, just with the unique words.
            }                                            //We'll use it as a lookup table later. So occurrences are 0.
            BinaryTree.insert(word);
        }
        ifs.close();


        wordsHolder = new string[uniqueCount];
        numsHolder = new int[uniqueCount];
        /*
         *  The unordered array is currently filled with all the unique words, but their frequencies aren't calculated yet.
         *  The hashtable has both, so we loop through every value in the Unordered Array and set it's appearances as the
         *  return value of a search in the hashtable.
         *  This significantly cuts down on the time needed to initialize each data structure.
         *  eg. ~6 hours to fill the unorderedArray AND calculate frequencies using the built-in functions with the large file
         *  Now it takes approximately 100 seconds to fill both the hashtable and the unordered array. Just 4s increase over
         *  just filling the hashtable.
         */
        for (long i = 0; i < uniqueCount; ++i) {
            wordsHolder[i] = unorderedArray.getData(i);
            numsHolder[i] = HashTable.search(wordsHolder[i]);
            unorderedArray.setNum(i, numsHolder[i]);
        }
        OrderedArray.copyFromUnordered(wordsHolder, numsHolder, uniqueCount);

        printf("Unique words: %ld.\n", uniqueCount);
        printf("Total words: %ld.\n", count);


    } else
        cout << "File error" << endl;

    return count;
}

void timeQSearches(int searchCount, UnorderedArray &unorderedArray, hashTable &HashTable, orderedArray &OrderedArray, BSTree &BinaryTree){
    string words[searchCount];
    int value;
    srand(searchCount);
    for (int i = 0; i < searchCount; ++i) {
        value = rand() % searchCount;
        words[i] = unorderedArray.getData(value);
    }

    auto begin = high_resolution_clock::now(), end = high_resolution_clock::now() ;
    duration<double, milli> elapsed = end - begin;
    long count;

    count = 0;
    begin = high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {count += unorderedArray.search(words[i]);}
    end = high_resolution_clock::now();
    elapsed = end - begin;
    cout<<"Searching "<<searchCount<<" words in the Unordered Array yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;

    count = 0;
    begin = high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {count += OrderedArray.search(words[i]);}
    end = high_resolution_clock::now();
    elapsed = end - begin;
    cout<<"Searching "<<searchCount<<" words in the Ordered Array yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;

    count = 0;
    begin = high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {count += BinaryTree.search(words[i]);}
    end = high_resolution_clock::now();
    elapsed = end - begin;
    cout<<"Searching "<<searchCount<<" words in the Ordered Array yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;

//      ------ Reserved for the AVL tree -----
//    count = 0;
//    begin = high_resolution_clock::now();
//    for (int i = 0; i < searchCount; ++i) {count += BinaryTree.search(words[i]);}
//    end = high_resolution_clock::now();
//    elapsed = end - begin;
//    cout<<"Searching "<<searchCount<<" words in the Ordered Array yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;

    count = 0;
    begin = high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {count += HashTable.search(words[i]);}
    end = high_resolution_clock::now();
    elapsed = end - begin;
    cout<<"Searching "<<searchCount<<" words in the Hash Table yielded "<<count<<" results in "<<elapsed.count()<<"ms"<<endl;

}




#endif //TEST_MAINFUNCTIONS_H
