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
    void balance(BTNode *);
    void rr_rotate(BTNode *);
    void ll_rotate(BTNode *);
    void rl_rotate(BTNode *);
    void lr_rotate(BTNode *);
    void insertAVL(BTNode *, string &);
public:
    AVLtree();
    void insert(string &);
    bool deleteWord(const string &);
};


#endif //TEST_AVLTREE_H
