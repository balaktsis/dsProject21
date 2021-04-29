#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "UnorderedArray.h"
#include "hashTable.h"
#include "orderedArray.h"

#ifndef TEST_MAINFUNCTIONS_H
#define TEST_MAINFUNCTIONS_H


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

long initStructures(const string &filename, UnorderedArray &unorderedArray, hashTable &HashTable, orderedArray &OrderedArray) {
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
                unorderedArray.InsertUnique(word, 0);    //Initializing the unordered array, just with the unique words.
            }                                            //We'll use it as a lookup table later. So occurrences are 0.
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



        string searchword = "ferrari";
        printf("\"%s\" appeared %d times in the Hash Table.\n", searchword.c_str(), HashTable.search(searchword));
        int pos, appearances;
        unorderedArray.Search(searchword, pos, appearances);
        printf("\"%s\" appeared %d times in the Unordered Table.\n", searchword.c_str(), appearances);
        printf("\"%s\" appeared %d times in the Ordered Table.\n", searchword.c_str(), OrderedArray.search(searchword));
        printf("Unique words: %ld.\n", uniqueCount);
        printf("Total words: %ld.\n", count);


    } else
        cout << "File error" << endl;

    return count;
}


#endif //TEST_MAINFUNCTIONS_H
