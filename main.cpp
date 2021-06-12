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
    bool unordered, ordered, binary, avl, hash, export_results;
    string filename;
};

string wordStrip(const string &word);
long
initStructures(config Config, UnorderedArray &unorderedArray, hashTable &HashTable, orderedArray &OrderedArray,
               BSTree &BinaryTree, AVLTree &AvlTree);
void
timeQSearches(config Config, long fileWords, long Q, UnorderedArray &unorderedArray, hashTable &HashTable,
              orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree);

template<typename searchable>
void calcSearch(searchable &structure, long searchCount, string *words, string arrName, bool export_results);


int main() {


    //Declaring variables for each data structure (Uninitialized)
    hashTable HashTable;
    UnorderedArray unorderedArray;
    orderedArray OrderedArray;
    BSTree BinaryTree;
    AVLTree AvlTree;

    config Config{
            Config.unordered = true,
            Config.ordered = true,
            Config.binary = true,
            Config.avl = true,
            Config.hash = true,

            Config.export_results = false    //If true, the results will be written to a file. Will have an adverse effect to performance
    };

    Config.filename = "small-file.txt";   //Name of the input file ('../' is needed for the project to compile on CLion)



    printf("Filling up the arrays...\n");

    //Fill up the data structures from the file.
    long filewords = initStructures(Config, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);


    //Search benchmark (first parameter being the random word count - Q)
    timeQSearches(Config, filewords, 5000, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);


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
initStructures(config Config, UnorderedArray &unorderedArray, hashTable &HashTable, orderedArray &OrderedArray,
               BSTree &BinaryTree, AVLTree &AvlTree) {
    long count = 0;
    long uniqueCount = 0;
    string word;

    // Timing
    auto begin = high_resolution_clock::now(), end = high_resolution_clock::now() ;
    duration<double> elapsed = end - begin;


    ifstream ifs;
    ifs.open(Config.filename);
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


        end = high_resolution_clock::now();
        elapsed = end - begin;
        cout<<"Filled up the structures in: "<<elapsed.count()<<"s"<<endl;


        printf("Total words: %ld.\n", count);


    } else
        cout << "File error" << endl;

    return count;
}

template<typename searchable>
void calcSearch(searchable &structure, long searchCount, string *words, string arrName, bool export_results) {


    /*
     * Calculating the time to search all Q randomly picked words in each structure.
     * count    : Counts the words returned, useful in order to validate the results
     * begin    : Timestamp at the start of the search
     * for loop : Iterating through every word in words (initialized earlier) and doing a search for it in each
     * structure, increasing count by the return value.
     * end      : Timestamp at the end of the search
     * elapsed  : Time between end and begin in milliseconds.
     */




    ofstream output;
    string filename;
    filename = arrName + ", Q:  " + to_string(searchCount);
    output.open (filename);


    long long count = 0;
    long tempcount = 0;

    auto begin = high_resolution_clock::now();

    for (long i = 0; i < searchCount; ++i) {
        tempcount = structure.search(words[i]);
        count += tempcount;
        if(export_results) {
            output << words[i] << " - " << tempcount << endl;
        }
    }


    auto end = high_resolution_clock::now();

    output.close();

    duration<double, milli> elapsed = end - begin;

    cout<<"Searching "<<searchCount<<" words in "<<arrName<<" yielded "<<count<<" results in ";
    printf(" %.4lf ms\n", elapsed.count());
//    cout<<""<<searchCount<<" - "<<arrName;
//    printf(" - %.4lf\n", elapsed.count());
}



void
timeQSearches(config Config, long fileWords, long Q, UnorderedArray &unorderedArray, hashTable &HashTable,
              orderedArray &OrderedArray, BSTree &BinaryTree, AVLTree &AvlTree) {

    string *words;
    words = new string[Q];

    long step = fileWords / Q;              //Creating a semi-randomised fingerprint of the total word pool
    long *wordIndex;
    wordIndex = new long[Q];
    srand(Q);
    for (long i = 0; i < Q; ++i) {

        wordIndex[i] = (rand() % step) + step * i;
    }



    ifstream ifs;
    ifs.open(Config.filename);
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
        calcSearch(unorderedArray, Q, words, "Unordered Array", Config.export_results);

    //Timing for the Ordered Array
    if (Config.ordered)
        calcSearch(OrderedArray, Q, words, "Ordered Array", Config.export_results);

    //Timing for the Binary Search Tree
    if (Config.binary)
        calcSearch(BinaryTree, Q, words, "Binary Search Tree", Config.export_results);

    //Timing for the AVL tree
    if (Config.avl)
        calcSearch(AvlTree, Q, words, "AVL Tree", Config.export_results);

    //Timing for the Hash Table
    if (Config.hash)
        calcSearch(HashTable, Q, words, "Hash Table", Config.export_results);

    delete[] words;
    delete[] wordIndex;

}