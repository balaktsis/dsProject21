#include <string>
#include "mainFunctions.h"


using namespace std;
using namespace std::chrono;


int main() {

    string filename = "../medium-file.txt";   //Name of the input file ('../' is needed for the project to compile on CLion)

    //Declaring variables for each data structure (Uninitialized)
    hashTable HashTable;
    UnorderedArray unorderedArray;
    orderedArray OrderedArray;
    BSTree BinaryTree;
    avl_tree AvlTree;



    printf("Filling up the arrays...\n");
    double count = initStructures(filename, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);


    //Search benchmark (first parameter being the random word count - Q)
    timeQSearches(1000, unorderedArray, HashTable, OrderedArray, BinaryTree, AvlTree);

}