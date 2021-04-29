#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "mainFunctions.h"


using namespace std;



int main() {

    string filename = "../small-file.txt";


    hashTable HashTable(1000000); //small-file: ideal about 5k //gutenberg: 1.000.000
    UnorderedArray unorderedArray;
    orderedArray OrderedArray;
    //binaryTree BinaryTree;
    //avlBinaryTree AvlBinaryTree;


    time_t begin,end; // time_t is a datatype to store time values.
    time (&begin); // note time before execution

    double count = initStructures(filename, unorderedArray, HashTable, OrderedArray);
    time(&end);

    double difference = difftime (end,begin);

//    cout<<count<<endl;
    cout<<"Total time: "<<difference<<" seconds.";
}