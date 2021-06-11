//
// Created by Christos Balaktsis on 28/4/2021.
//

#include "BSTree.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

BSTree::BSTree() {
    root = nullptr;
}

BSTree::~BSTree() {
    deleteBST();
}

void BSTree::insert(const string &data) {
    root = insert(root,data);
}

long BSTree::getHeight() {
    return getHeight(root);
}

void BSTree::deleteBST() {
    deleteBST(root);
}

void BSTree::postOrder() {
    ofstream f;
    f.open("BST_Post_Order.txt",ios::out);
    if(f.is_open())
        postOrder(root,f);
    f.close();
}

void BSTree::preOrder() {
    ofstream f;
    f.open("BST_Pre_Order.txt",ios::out);
    if(f.is_open())
        preOrder(root,f);
    f.close();
}

void BSTree::inOrder() {
    ofstream f;
    f.open("BST_In_Order.txt",ios::out);
    if(f.is_open())
        inOrder(root,f);
    f.close();
}

BTNode * BSTree::insert(BTNode *tNode, const string &data) {
    if (tNode == nullptr) {                                         //Putting string in a new leaf.
        tNode = new BTNode(data);
    }
    else {
        if (data == tNode->data) {                                  //String already exists - update number of occurrences.
            tNode->num += 1;
        }
        else {                                                      //New string - finding the correct place to get it saved.
            if (data < tNode->data) {                               //If string is < than current node's string, it should be place left to current node.
                if (tNode->left == nullptr) {                       //Putting string in a new leaf.
                    BTNode *temp = new BTNode(data);
                    tNode->left = temp;
                }
                else {                                              //String should be place left to current node, but there's
                    insert(tNode->left, data);                      //another one, so it should be compared to current's child.
                }
            }
            else {                                                  //String should be placed right to current node.
                if (tNode->right == nullptr) {                      //Corresponding to the above.
                    BTNode *temp = new BTNode(data);
                    tNode->right = temp;
                }
                else {
                    insert(tNode->right, data);
                }
            }
        }
    }
    return tNode;
}

bool BSTree::deleteWord(const string &word) {
    BTNode *p = root;                                     //Search pointer.
    BTNode *pp = nullptr;                                 //Parent of p.
    while(p && p->data != word) {                         //Move to a child of p. Search for node storing word.
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
    if(p->left && p->right) {                           //Handling case when p has 2 children. Converting to zero or one child case.
        BTNode *s = p->left;
        BTNode *ps = p;                                 //Parent of data.
        while (s->right) {                              //Find largest element in left subtree of p.
            ps = s;
            s = s->right;
        }
        p->data = s->data;                              //Move largest from data to p, so the given word gets replaced.
        p = s;
        pp = ps;
    }                                                   //Now, p kept at most one child. On the right or on the left.
    BTNode *c=nullptr;                                  //Save child in c.
    if (p->left)
        c = p->left;
    else
        c = p->right;
                                                        //Set p's parent pointing to s's child.
    if (p == root)
        root = c;
    else if (p == pp->left)
        pp->left = c;
    else
        pp->right = c;
    delete p;                                           //Deletes the appropriate node.
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

void BSTree::inOrder(BTNode * tNode, ofstream &f) {
    if (tNode != nullptr) {
        inOrder(tNode->left,f);
        f << tNode->data << " : " << tNode->num << endl;
        inOrder(tNode->right,f);
    }
}

void BSTree::preOrder(BTNode * tNode, ofstream &f)
{
    if (tNode != nullptr) {
        f << tNode->data << " : " << tNode->num << endl;
        preOrder(tNode->left,f);
        preOrder(tNode->right,f);
    }
}

void BSTree::postOrder(BTNode * tNode, ofstream &f) {
    if (tNode != nullptr) {
        postOrder(tNode->left,f);
        postOrder(tNode->right,f);
        f << tNode->data << " : " << tNode->num << endl;
    }
}

int BSTree::search(const string &word) {
    BTNode *p = root;                                     //Search pointer.
    while (p) {                                           //While p is not NULL, move to the appropriate sub-tree to find the string/
        if (word < p->data) {
            p = p->left;
        } else {
            if (word > p->data)
                p = p->right;
            else {
                return p->num;                          //Returns number of occurrences of string in text-file.
            }
        }
    }
    return 0;                                          //Word not existed in text-file or deleted from BSTree object.
}