//
// Created by Christos Balaktsis on 11/5/2021.
//

#ifndef TEST_AVLTREE_H
#define TEST_AVLTREE_H
#include "BSTree.h"
#include <string>

struct avl {
    int d;
    string s;
    struct avl *l;
    struct avl *r;
};
class avl_tree {
private:
    avl *r;
public:
    long height(avl *);
    long difference(avl *);
    avl *rr_rotat(avl *);
    avl *ll_rotat(avl *);
    avl *lr_rotat(avl*);
    avl *rl_rotat(avl *);
    avl * balance(avl *);
    avl * insert(avl*, string &);
    void insert(string &);
    //void show(avl*, string);//
    void inorder(avl *);
    void preorder(avl *);
    void postorder(avl*);
    avl_tree() {
        r = NULL;
    }
    int search(string &);
};
#endif //TEST_AVLTREE_H
