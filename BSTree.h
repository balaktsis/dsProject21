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
   BTNode *left;
   BTNode *right;
   BTNode() {
       left = nullptr;
       right = nullptr;
   }
   BTNode(const string &word) {
       data = word;
       left = nullptr;
       right = nullptr;
   }
   BTNode(const string &word, BTNode *l, BTNode *r) {
       data = word;
       right = r;
       left = l;
   }
};

class BSTree {
protected:
    BTNode *root;
    void insert(BTNode*, string);
    bool isBalanced(BTNode*);
    long getHeight(BTNode*);
    void deleteBST(BTNode*);
    void inOrder(BTNode*);
    void preOrder(BTNode*);
    void postOrder(BTNode*);
public:
    BSTree();                                           //Constructs a new Binary Search Tree.
    ~BSTree();                                          //Destructor of Binary Search Tree.
    void insert(string data);                           //Inserts new string (node) in BST.
    long getHeight();                                   //Returns height of BTS.
    BTNode * getMaxNode();
    BTNode * getMinNode();
    void deleteBST();
    bool isBalanced();
    void inOrder();
    void preOrder();
    void postOrder();
};

#endif //TEST_BSTREE_H
