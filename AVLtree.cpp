//
// Created by Christos Balaktsis on 11/5/2021.
//

#include "AVLtree.h"

AVLtree::AVLtree():BSTree() {}

AVLtree::~AVLtree() {
    deleteBST();
}

long AVLtree::difference(BTNode *node) {
    long l_height = BSTree::getHeight(node->left);
    long r_height = BSTree::getHeight(node->right);
    long b_factor = l_height - r_height;
    return b_factor;
}

BTNode * AVLtree::rr_rotate(BTNode *parent) {
    BTNode *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

BTNode * AVLtree::ll_rotate(BTNode *parent) {
    BTNode *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

BTNode * AVLtree::lr_rotate(BTNode *parent) {
    BTNode *temp;
    temp = parent->left;
    parent->left = rr_rotate(temp);
    return ll_rotate(parent);
}

BTNode * AVLtree::rl_rotate(BTNode *parent) {
    BTNode *temp;
    temp = parent->right;
    parent->right = ll_rotate(temp);
    return rr_rotate(parent);
}

BTNode * AVLtree::balance(BTNode *temp) {
    int bal_factor = difference(temp);
    if (bal_factor > 1) {
        if (difference(temp->left) > 0)
            temp = ll_rotate(temp);
        else
            temp = lr_rotate(temp);
    }
    else
        if (bal_factor < -1) {
            if (difference(temp->right) > 0)
                temp = rl_rotate(temp);
            else
                temp = rr_rotate(temp);
    }
    return temp;
}

void AVLtree::insert(string &word) {
    root = insertAVL(root, word);
}


BTNode * AVLtree::insertAVL(BTNode *r, string &v) {
    if (r == nullptr) {
        r = new BTNode;
        r->data = v;
        r->num = 1;
        r->left = nullptr;
        r->right = nullptr;
        return r;
    } else if (v< r->data) {
        r->left = insertAVL(r->left, v);
        r = balance(r);
    } else if (v > r->data) {
        r->right = insertAVL(r->right, v);
        r = balance(r);
    } else {
        r->num += 1;
    }
    return r;
}