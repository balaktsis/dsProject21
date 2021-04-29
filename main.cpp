#include <iostream>
#include <fstream>
#include <string>
//#include <ctime>
#include <chrono>
#include "mainFunctions.h"


using namespace std;
using namespace std::chrono;


int main() {

    string filename = "../gutenberg.txt";   //Name of the input file ('../' is needed for the project to compile on CLion)

    //Declaring variables for each data structure (Uninitialized)
    hashTable HashTable(1000000); //small-file: ideal about 5.000 //gutenberg: 1.000.000
    UnorderedArray unorderedArray;
    orderedArray OrderedArray;
    BSTree BinaryTree;
    //avlBinaryTree AvlBinaryTree;



    printf("Filling up the arrays...\n");
    double count = initStructures(filename, unorderedArray, HashTable, OrderedArray, BinaryTree);

    timeQSearches(10000, unorderedArray, HashTable, OrderedArray, BinaryTree);

}