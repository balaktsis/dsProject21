#include "AVLtree.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

AVLTree::AVLTree() {
    root = nullptr;
}

AVLTree::~AVLTree() {
    deleteAVL();
}

void AVLTree::deleteAVL() {
    deleteAVL(root);
}

void AVLTree::insert(const string &word) {
    root = insert(root, word);
}

long AVLTree::height(avlNode *tNode) {
    long h = 0;															
    if (tNode != nullptr) {												//Not checking a leaf or root.
        long l_height = height(tNode->left);							//Find height of left sub-tree.
        long r_height = height(tNode->right);							//Find height of right sub-tree.
        long max_height = max(l_height, r_height);						//Keep the maximum of the two and add 1, including root.
        h = max_height + 1;
    }
    return h;
}

long AVLTree::getHeight() {
    return height(root);
}

long AVLTree::difference(avlNode *tNode) {
    long l_height = height(tNode->left);								
    long r_height = height(tNode->right);
    long b_factor = l_height - r_height;
    return b_factor;
}

avlNode *AVLTree::rr_rotate(avlNode *parent) {
    avlNode *tNode;
    tNode = parent->right;
    parent->right = tNode->left;
    tNode->left = parent;
    return tNode;
}

avlNode *AVLTree::ll_rotate(avlNode *parent) {
    avlNode *tNode;
    tNode = parent->left;
    parent->left = tNode->right;
    tNode->right = parent;
    return tNode;
}

avlNode *AVLTree::lr_rotate(avlNode *parent) {
    avlNode *tNode;
    tNode = parent->left;
    parent->left = rr_rotate(tNode);
    return ll_rotate(parent);
}

avlNode *AVLTree::rl_rotate(avlNode *parent) {
    avlNode *t;
    t = parent->right;
    parent->right = ll_rotate(t);
    return rr_rotate(parent);
}

avlNode *AVLTree::balance(avlNode *tNode) {
    long bal_factor = difference(tNode);
    if (bal_factor > 1) {
        if (difference(tNode->left) >= 0)
            tNode = ll_rotate(tNode);
        else
            tNode = lr_rotate(tNode);
    }
    else
        if (bal_factor < -1) {
            if (difference(tNode->right) > 0)
                tNode = rl_rotate(tNode);
            else
                tNode = rr_rotate(tNode);
    }
    return tNode;
}

avlNode *AVLTree::insert(avlNode *tNode, const string &word) {
    if (tNode == nullptr) {												//Putting string in a new leaf.
        tNode = new avlNode(word);
        return tNode;
    } else if (word < tNode->data) {									//If string is < than current node's string, it should be place left to current node.
        tNode->left = insert(tNode->left, word);						//Putting string in a new leaf.
        tNode = balance(tNode);											//Checking and fixing tree's balance state.
    } else if (word > tNode->data) {									//Corresponding to the above.
        tNode->right = insert(tNode->right, word);						
        tNode = balance(tNode);
    } else { tNode->num = tNode->num + 1;}						 		//String already exists - update number of occurrences.
    return tNode;
}

void AVLTree::inOrder(avlNode *tNode, ofstream &f) {
    if (tNode == nullptr)
        return;
    inOrder(tNode->left, f);
    f << tNode->data << " : " << tNode->num << endl;
    inOrder(tNode->right, f);
}

void AVLTree::preOrder(avlNode *tNode, ofstream &f) {
    if (tNode == nullptr)
        return;
    f << tNode->data << " : " << tNode->num << endl;
    preOrder(tNode->left, f);
    preOrder(tNode->right, f);
}

void AVLTree::postOrder(avlNode *tNode, ofstream &f) {
    if (tNode == nullptr)
        return;
    postOrder(tNode->left, f);
    postOrder(tNode->right, f);
    f << tNode->data << " : " << tNode->num << endl;
}

int AVLTree::search(const string &word) {
    avlNode *p = root;                                    				//Search pointer
    while (p) {															//While p is not NULL, move to the appropriate sub-tree to find the string.
        if (word < p->data) {
            p = p->left;
        } else {
            if (word > p->data)
                p = p->right;
            else {
                return p->num;											//Returns number of occurrences of string in text-file.
            }
        }
    }
    return 0;															//Word not existed in text-file or deleted from AVLTree object.
}

bool AVLTree::deleteWord(const string &word) {
    avlNode *p = root;                                   				//Search pointer.
    avlNode *pp = nullptr;                               			  	//Parent of p.
    while(p && p->data != word) {                        			 	//Move to a child of p. Search for node storing word.
        pp = p;
        if(word < p-> data) {
            p = p->left;
        }
        else {
            p = p->right;
        }
    }
    if(!p)                                              				//Node not found.
        return false;
    if(p->left && p->right) {                          	 				//Handling case when p has 2 children. Converting to zero or one child case.
        avlNode *s = p->left;
        avlNode *ps = p;                                 				//Parent of data.
        while (s->right) {                             				 	//Find largest element in left subtree of p.
            ps = s;
            s = s->right;
        }
        p->data = s->data;                           				   	//Move largest from data to p, so the given word gets replaced.
        p = s;
        pp = ps;
    }                                                   				//Now, p kept at most one child. On the right or on the left.
    avlNode *c=nullptr;                                				  	//Save child in c.
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
    delete p;															//Deletes the appropriate node.
    root = balance(root);												//Checking and fixing tree's balance state.
    return true;
}

void AVLTree::postOrder() {
    ofstream f;
    f.open("AVL_Post_Order.txt", ios::out);
    if(f.is_open())
        postOrder(root,f);
    f.close();
}

void AVLTree::preOrder() {
    ofstream f;
    f.open("AVL_Pre_Order.txt", ios::out);
    if(f.is_open())
        preOrder(root,f);
    f.close();
}

void AVLTree::inOrder() {
    ofstream f;
    f.open("AVL_In_Order.txt", ios::out);
    if(f.is_open())
        inOrder(root,f);
    f.close();
}

void AVLTree::deleteAVL(avlNode *tNode) {
    if (tNode != nullptr) {
        avlNode *curNode = tNode;
        avlNode *leftNode = tNode->left;
        avlNode *rightNode = tNode->right;
        delete (curNode);
        deleteAVL(leftNode);
        deleteAVL(rightNode);
    }
}