//
// Created by Christos Balaktsis on 11/5/2021.
//

#ifndef TEST_AVLTREE_H
#define TEST_AVLTREE_H
#include <iostream>
#include <string>

using namespace std;

struct avlNode {
    string data;									//Word given in text-file.
    int num;										//Number of occurrences of word in text-file.	
	avlNode *left;									//Left sub-tree/node-child.
    avlNode *right;									//Right sub-tree/node-child.
    avlNode(){
        left = nullptr;
        right = nullptr;
    }
    avlNode(const string &word) {
        data = word;
        left = nullptr;
        right = nullptr;
        num = 1;
    }
};

class AVLTree {
private:
    avlNode *root;									//Root pointer of AVLTree.
    long height(avlNode *);							//Returns current height of the tree: the longest path from root to a leaf.
    long difference(avlNode *);						//Returns height-difference between two sub-trees.
    avlNode * rr_rotate(avlNode *);					//Right-Right node rotation of sub-tree.	
    avlNode * ll_rotate(avlNode *);					//Left-Left node rotation of sub-tree.
    avlNode * lr_rotate(avlNode*);					//Left-Right node rotation of sub-tree.
    avlNode * rl_rotate(avlNode *);					//Right-Left node rotation of sub-tree.
    avlNode * balance(avlNode *);					//Checks and sets tree to AVL - balanced version, max(difference)=1.
    avlNode * insert(avlNode*, const string &);		//Recursive node-height addition. Finds the longest route from root to a leaf.
    void inOrder(avlNode *);						//Recursive in-ordered node showing. Begins with root node.
    void preOrder(avlNode *);						//Recursive pre-ordered node showing. Begins with root node.
    void postOrder(avlNode*);						//Recursive post-ordered node showing. Begins with root node.
    void deleteAVL(avlNode*);						//Recursive node deletion. Begins with root, root's children etc.
    void deleteAVL();                               //Deletes AVL Binary Search Tree.
public:
    AVLTree();										//Constructs a new AVL Binary Search Tree.
    ~AVLTree();                                     //Destructor of AVL Binary Search Tree.
    int search(const string &);                     //Searches a word in AVL (returns 0 if word does not exist, or its number of occurrences in text).
    void insert(const string &);					//Inserts new string (node) in AVLTree.
    bool deleteWord(const string &);				//Deletes a word of the AVLTree (returns true if word exists).
    void inOrder();									//In-ordered nodes showing.
    void preOrder();								//Pre-ordered nodes showing.
    void postOrder();								//Post-ordered nodes showing.
    long getHeight();                               //Returns height of AVLTree.
};

#endif //TEST_AVLTREE_H
