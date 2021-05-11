//
// Created by Christos Balaktsis on 11/5/2021.
//

#include "AVLtree.h"
#include <iostream>

AVLtree::AVLtree() {
    root = nullptr;
}


long AVLtree::difference(BTNode *node) {
    long l_height = BSTree::getHeight(node->left);
    long r_height = BSTree::getHeight(node->right);
    long b_factor = l_height - r_height;
    return b_factor;
}

void AVLtree::rr_rotate(BTNode *parent) {
    BTNode *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
}

void AVLtree::ll_rotate(BTNode *parent) {
    BTNode *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
}

void AVLtree::lr_rotate(BTNode *parent) {
    BTNode *temp;
    temp = parent->left;
    rr_rotate(temp);
    ll_rotate(parent);
}

void AVLtree::rl_rotate(BTNode *parent) {
    BTNode *temp;
    temp = parent->right;
    ll_rotate(temp);
    rr_rotate(parent);
}

void AVLtree::balance(BTNode *temp) {
    int bal_factor = difference(temp);
    if (bal_factor > 1) {
        if (difference(temp->left) > 0)
            ll_rotate(temp);
        else
            lr_rotate(temp);
    }
    else
    if (bal_factor < -1) {
        if (difference(temp->right) > 0)
            rl_rotate(temp);
        else
            rr_rotate(temp);
    }
}

void AVLtree::insert(string &word) {
    insertAVL(root, word);
}

void AVLtree::insertAVL(BTNode *tNode, string &data) {
    if (tNode == nullptr) {
        tNode = new BTNode(data);
        root = tNode;
        balance(tNode);
    }
    else {
        if (data == tNode->data) {
            tNode->num += 1;
        }
        else {
            if (data < tNode->data) {
                if (tNode->left == nullptr) {
                    BTNode *temp = new BTNode(data);
                    tNode->left = temp;
                    balance(tNode);
                }
                else {
                    insertAVL(tNode->left, data);
                }
            }
            else {
                if (tNode->right == nullptr) {
                    BTNode *temp = new BTNode(data);
                    tNode->right = temp;
                    balance(tNode);

                }
                else {
                    insertAVL(tNode->right, data);
                }
            }
        }
    }
}
