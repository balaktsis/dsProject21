//
// Created by Christos Balaktsis on 11/5/2021.
//

#ifndef TEST_AVLTREE_H
#define TEST_AVLTREE_H
#include "BSTree.h"
#include <string>

class AVLtree : public BSTree {
protected:
    long difference(BTNode *);
    BTNode * balance(BTNode *);
    BTNode * rr_rotate(BTNode *);
    BTNode * ll_rotate(BTNode *);
    BTNode * rl_rotate(BTNode *);
    BTNode * lr_rotate(BTNode *);
    BTNode * insertAVL(BTNode *, string &);
public:
    AVLtree();
    ~AVLtree();
    void insert(string &);
    bool deleteWord(const string &);
};


#endif //TEST_AVLTREE_H
