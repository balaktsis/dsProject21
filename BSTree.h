//
// Created by Christos Balaktsis on 28/4/2021.
//

#ifndef TEST_BSTREE_H
#define TEST_BSTREE_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct BTNode {
    string data;                                        //Word given in text-file.
    int num;                                           	//Number of occurrences of word in text-file.							
    BTNode *left;                                       //Left sub-tree/node-child.
    BTNode *right;                                      //Right sub-tree/node-child.
    BTNode() {
        left = nullptr;
        right = nullptr;
    }
    BTNode(const string &word) {
        data = word;
        num = 1;
        left = nullptr;
        right = nullptr;
    }
    BTNode(const string &word, BTNode *l, BTNode *r) {
        num = 1;
        data = word;
        right = r;
        left = l;
    }
};

class BSTree {
protected:
    BTNode *root;									   //Root pointer of BST.
    BTNode *insert(BTNode*, const string&);            //Takes a node and attempts to insert string in it or in its subtrees. Begins with root node.
    long getHeight(BTNode*);                           //Recursive node-height addition. Finds the longest route from root to a leaf.
    void deleteBST(BTNode*);                           //Recursive node deletion. Begins with root, root's children etc.
    void inOrder(BTNode*, ofstream&);                  //Recursive in-ordered node showing. Begins with root node.
    void preOrder(BTNode*, ofstream&);                 //Recursive pre-ordered node showing. Begins with root node.
    void postOrder(BTNode*, ofstream&);                //Recursive post-ordered node showing. Begins with root node.
    void deleteBST();                                  //Deletes Binary Search Tree.
public:
    BSTree();                                          //Constructs a new Binary Search Tree.
    ~BSTree();                                         //Destructor of Binary Search Tree.
    void insert(const string &);                       //Inserts new string (node) in BST.
    bool deleteWord(const string &);                   //Deletes a word of the BST (returns true if word exists).
    int search(const string &);                        //Searches a word in BST (returns 0 if word does not exist, or its number of occurrences in text).
    long getHeight();                                  //Returns height of BST.
    void inOrder();                                    //In-ordered nodes showing.
    void preOrder();                                   //Pre-ordered nodes showing.
    void postOrder();                                  //Post-ordered nodes showing.
};

#endif //TEST_BSTREE_H
