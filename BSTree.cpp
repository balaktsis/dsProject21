//
// Created by Christos Balaktsis on 28/4/2021.
//

#include "BSTree.h"
#include <iostream>
#include <string>
using namespace std;

BSTree::BSTree() {
    root = nullptr;
}

/*BSTree::~BSTree() {
    deleteBST();
}*/

void BSTree::insert(string &data) {
    insert(root,data);
}

long BSTree::getHeight() {
    return getHeight(root);
}

void BSTree::deleteBST() {
    deleteBST(root);
}

void BSTree::postOrder() {
    postOrder(root);
}

void BSTree::preOrder() {
    preOrder(root);
}

void BSTree::inOrder() {
    inOrder(root);
}

void BSTree::insert(BTNode *tNode, string &data) {
    if (tNode == nullptr) {
        tNode = new BTNode(data);
        root = tNode;
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
                }
                else {
                    insert(tNode->left, data);
                }
            }
            else {
                if (tNode->right == nullptr) {
                    BTNode *temp = new BTNode(data);
                    tNode->right = temp;
                }
                else {
                    insert(tNode->right, data);
                }
            }
        }
    }
}

bool BSTree::deleteWord(string &word) {
    BTNode *p = root;                                     //Search pointer.
    BTNode *pp = nullptr;                                 //Parent of p.
    while(p && p->data != word) {
        pp = p;
        if(word < p-> data) {
            p = p->left;
        }
        else {
            p = p->right;
        }
    }
    if(!p)                                              //Node not found.
        return false;
    //Handling case when p has 2 children.
    if(p->left && p->right) {
        BTNode *s = p->left;
        BTNode *ps = p;                                 //Parent of s.
        while (s->right) {
            ps = s;
            s = s->right;
        }
        p->data = s->data;
        p = s;
        pp = ps;
        BTNode *c;
        if (p->left)
            c = p->left;
        else
            c = p->right;
        //Delete node p.
        if (p == root)
            root = c;
        else if (p == pp->left)
            pp->left = c;
        else
            pp->right = c;
    }
    delete p;
    return true;
}

long BSTree::getHeight(BTNode *tNode) {
    if(tNode == nullptr)
        return 0;
    else
        return 1 + max(getHeight(tNode->left), getHeight(tNode->right));
}

void BSTree::deleteBST(BTNode *tNode) {
    if (tNode != nullptr) {
        BTNode *curNode = tNode;
        BTNode *leftNode = tNode->left;
        BTNode *rightNode = tNode->right;
        delete (curNode);
        deleteBST(leftNode);
        deleteBST(rightNode);
    }
}

void BSTree::inOrder(BTNode * tNode) {
    if (tNode != nullptr) {
        inOrder(tNode->left);
        cout << tNode->data << " : " << tNode->num << endl;
        inOrder(tNode->right);
    }
}

void BSTree::preOrder(BTNode * tNode)
{
    if (tNode != nullptr) {
        cout << tNode->data << " : " << tNode->num << endl;
        preOrder(tNode->left);
        preOrder(tNode->right);
    }
}

void BSTree::postOrder(BTNode * tNode) {
    if (tNode != nullptr) {
        postOrder(tNode->left);
        postOrder(tNode->right);
        cout << tNode->data << " : " << tNode->num << endl;
    }
}

int BSTree::search(string &word) {
    BTNode *p = root;                                     //Search pointer.
    while (p) {
        if (word < p->data) {
            p = p->left;
        } else {
            if (word > p->data)
                p = p->right;
            else {
                return p->num;
            }
        }
    }
    return 0;
}