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

class config{
public:
    bool unordered, ordered, binary, avl, hash;
};

string wordStrip(const string &word);
long
initStructures(config Config, const string &filename, UnorderedArray &unorderedArray, hashTable &HashTable,
               orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree);
void
timeQSearches(config Config, long fileWords, const string &filename, long Q, UnorderedArray &unorderedArray,
              hashTable &HashTable, orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree);

template<typename searchable>
void calcSearch(searchable &structure, long searchCount, string *words, string arrName);


int main() {

    string filename = "../small-file.txt";   //Name of the input file ('../' is needed for the project to compile on CLion)

    //Declaring variables for each data structure (Uninitialized)
    hashTable HashTable;
    UnorderedArray unorderedArray;
    orderedArray OrderedArray;
    BSTree BinaryTree;
    AVLTree AvlTree;

    config Config{
            Config.unordered = false,
            Config.ordered = false,
            Config.binary = true,
            Config.avl = false,
            Config.hash = true
    };



    printf("Filling up the arrays...\n");

    //Fill up the data structures from the file.
    long filewords = initStructures(Config, filename, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);


    //Search benchmark (first parameter being the random word count - Q)

    timeQSearches(Config, filewords, filename, 1000, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);
    timeQSearches(Config, filewords, filename, 3000, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);
    timeQSearches(Config, filewords, filename, 5000, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);
    timeQSearches(Config, filewords, filename, 7000, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);
    timeQSearches(Config, filewords, filename, 10000, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);
    timeQSearches(Config, filewords, filename, 15000, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);

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

long
initStructures(config Config, const string &filename, UnorderedArray &unorderedArray, hashTable &HashTable,
               orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree) {
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
            if (count%25000000 == 0){cout<<"Filled "<<count/1000000<<"mil words\n";}

            if (Config.unordered)
                unorderedArray.insert(word);

            if (Config.ordered)
                OrderedArray.insert(word);

            if (Config.binary)
                BinaryTree.insert(word);

            if (Config.avl)
                AvlTree.insert(word);

            if (Config.hash)
                HashTable.insert(word);

        }
        ifs.close();
//        uniqueCount = HashTable.getSize();

        end = high_resolution_clock::now();
        elapsed = end - begin;
        cout<<"Filled up the structures in: "<<elapsed.count()<<"s"<<endl;

//        printf("Unique words: %ld.\n", uniqueCount);
        printf("Total words: %ld.\n", count);

//        cout<<"Size of Unordered: "<<unorderedArray.getSize()<<endl;
//        cout<<"Size of Ordered: "<<OrderedArray.getSize()<<endl;
//        cout<<"Size of Hash Table: "<<HashTable.getSize()<<endl;

    } else
        cout << "File error" << endl;

    return count;
}

template<typename searchable>
void calcSearch(searchable &structure, long searchCount, string *words, string arrName){


    /*
     * Calculating the time to search all Q randomly picked words in each structure.
     * count    : Counts the words returned, useful in order to validate the results
     * begin    : Timestamp at the start of the search
     * for loop : Iterating through every word in words (initialized earlier) and doing a search for it in each
     * structure, increasing count by the return value.
     * end      : Timestamp at the end of the search
     * elapsed  : Time between end and begin in milliseconds.
     */

    long long count = 0;
    auto begin = high_resolution_clock::now();

    ofstream myfile;
    string filename;
    filename = arrName + " - " + to_string(searchCount);
    myfile.open (filename);

    long tempcount = 0;

    for (long i = 0; i < searchCount; ++i) {
        tempcount = structure.search(words[i]);
        count += tempcount;
        myfile<<words[i]<<" - "<<tempcount<<endl;
    }
    myfile.close();

    auto end = high_resolution_clock::now();

    duration<double, milli> elapsed = end - begin;

//    cout<<"Searching "<<searchCount<<" words in "<<arrName<<" yielded "<<count<<" results in ";
//    printf(" %.4lf ms\n", elapsed.count());
    cout<<""<<searchCount<<" - "<<arrName;
    printf(" - %.4lf\n", elapsed.count());
}



void
timeQSearches(config Config, long fileWords, const string &filename, long Q, UnorderedArray &unorderedArray,
              hashTable &HashTable, orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree) {

    string *words;
    words = new string[Q];

    long step = fileWords / Q;              //Creating a semi-randomised fingerprint of the total word pool
    long *wordIndex;
    wordIndex = new long[Q];
    srand(Q);
    for (long i = 0; i < Q; ++i) {

        wordIndex[i] = /*(rand() % step) +*/ step * i;
    }



    ifstream ifs;
    ifs.open(filename);
    ifs.seekg (0, ios::beg);
    if (!ifs.is_open()){
        cout<<"file error"<<endl;
        return;
    }


    long totalCount = 0 ,count = 0;
    string word;
    while (ifs >> word) {
        word = wordStrip(word);
        if (word.empty() || (0 <= word[0] && word[0] <= 32)) {
            continue;
        }

        if (totalCount == wordIndex[count]){
            words[count] = word;
            count++;
        }

        totalCount++;
        if (count == Q){
            break;
        }
    }

    ifs.close();


    //Timing for the Unordered Array
    if (Config.unordered)
        calcSearch(unorderedArray, Q, words, "Unordered Array");

    //Timing for the Ordered Array
    if (Config.ordered)
        calcSearch(OrderedArray, Q, words, "Ordered Array");

    //Timing for the Binary Search Tree
    if (Config.binary)
        calcSearch(BinaryTree, Q, words, "Binary Search Tree");

    //Timing for the AVL tree
    if (Config.avl)
        calcSearch(AvlTree, Q, words, "AVL Tree");

    //Timing for the Hash Table
    if (Config.hash)
        calcSearch(HashTable, Q, words, "Hash Table");

    delete[] words;
    delete[] wordIndex;

}