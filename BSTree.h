//
// Created by Christos Balaktsis on 28/4/2021.
//

#ifndef TEST_BSTREE_H
#define TEST_BSTREE_H
#include <iostream>
#include <string>
using namespace std;

struct BTNode {
    string data;
    long num;
    BTNode *left;
    BTNode *right;
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
    BTNode *root;
    void insert(BTNode*, string&);
    long getHeight(BTNode*);
    void deleteBST(BTNode*);
    void inOrder(BTNode*);
    void preOrder(BTNode*);
    void postOrder(BTNode*);
public:
    BSTree();                                          //Constructs a new Binary Search Tree.
    // ~BSTree();                                         //Destructor of Binary Search Tree.
    virtual void insert(string &);                             //Inserts new string (node) in BST.
    virtual bool deleteWord(string &);                         //Deletes a word of the BST (returns true if word exists).
    int search(string &);                             //Searches a word in BST (returns true if word exists).
    long getHeight();                                  //Returns height of BST.
    void deleteBST();                                  //Deletes Binary Search Tree.
    void inOrder();
    void preOrder();
    void postOrder();
};

#endif //TEST_BSTREE_H
