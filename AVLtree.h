//
// Created by Christos Balaktsis on 11/5/2021.
//

#ifndef TEST_AVLTREE_H
#define TEST_AVLTREE_H
#include <iostream>
#include <string>

using namespace std;

struct avlNode {
    int num;
    string data;
    avlNode *left;
    avlNode *right;
};

class AVLTree {
private:
    avlNode *root;
    long height(avlNode *);
    long difference(avlNode *);
    avlNode * rr_rotate(avlNode *);
    avlNode * ll_rotate(avlNode *);
    avlNode * lr_rotate(avlNode*);
    avlNode * rl_rotate(avlNode *);
    avlNode * balance(avlNode *);
    avlNode * insert(avlNode*, const string &);
    void inOrder(avlNode *);
    void preOrder(avlNode *);
    void postOrder(avlNode*);
    void deleteAVL(avlNode*);
    void deleteAVL();                                  //Deletes AVL Binary Search Tree.
public:
    AVLTree();
    ~AVLTree();                                         //Destructor of AVL Binary Search Tree.
    int search(const string &);
    void insert(const string &);
    bool deleteWord(const string &);
    void inOrder();
    void preOrder();
    void postOrder();
    long getHeight();                               //Returns height of AVLTree.
};

#endif //TEST_AVLTREE_H
