#include "AVLtree.h"
#include <string>
#include <iostream>
using namespace std;

void avl_tree::insert(string &word) {
    r = insert(r,word);
    // static long i=0;
    // cout<<"insertion"<<++i<<endl;
}

long avl_tree::height(avl *t) {
    long h = 0;
    if (t != NULL) {
        long l_height = height(t->l);
        long r_height = height(t->r);
        long max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
long avl_tree::difference(avl *t) {
    long l_height = height(t->l);
    long r_height = height(t->r);
    long b_factor = l_height - r_height;
    return b_factor;
}
avl *avl_tree::rr_rotat(avl *parent) {
    avl *t;
    t = parent->r;
    parent->r = t->l;
    t->l = parent;
    //cout<<"Right-Right Rotation";
    return t;
}
avl *avl_tree::ll_rotat(avl *parent) {
    avl *t;
    t = parent->l;
    parent->l = t->r;
    t->r = parent;
    //cout<<"Left-Left Rotation";
    return t;
}
avl *avl_tree::lr_rotat(avl *parent) {
    avl *t;
    t = parent->l;
    parent->l = rr_rotat(t);
    // cout<<"Left-Right Rotation";
    return ll_rotat(parent);
}
avl *avl_tree::rl_rotat(avl *parent) {
    avl *t;
    t = parent->r;
    parent->r = ll_rotat(t);
    //cout<<"Right-Left Rotation";
    return rr_rotat(parent);
}
avl *avl_tree::balance(avl *t) {
    long bal_factor = difference(t);
    if (bal_factor > 1) {
        if (difference(t->l) > 0)
            t = ll_rotat(t);
        else
            t = lr_rotat(t);
    } else if (bal_factor < -1) {
        if (difference(t->r) > 0)
            t = rl_rotat(t);
        else
            t = rr_rotat(t);
    }
    return t;
}
avl *avl_tree::insert(avl *r, string &v) {
    if (r == NULL) {
        r = new avl;
        r->s = v;
        r->l = NULL;
        r->r = NULL;
        r->d = 1;
        return r;
    } else if (v< r->s) {
        r->l = insert(r->l, v);
        r = balance(r);
    } else if (v > r->s) {
        r->r = insert(r->r, v);
        r = balance(r);
    } else {r->d = r->d+1;}
    return r;
}
/*void avl_tree::show(avl *p, int l) {
   long i;
   if (p != NULL) {
      show(p->r, l+ 1);
      cout<<" ";
      if (p == r)
         cout << "Root -> ";
      for (i = 0; i < l&& p != r; i++)
         cout << " ";
         cout << p->d;
         show(p->l, l + 1);
   }
}*/
void avl_tree::inorder(avl *t) {
    if (t == NULL)
        return;
    inorder(t->l);
    cout << t->s << ","<<t->d<<endl;
    inorder(t->r);
}
void avl_tree::preorder(avl *t) {
    if (t == NULL)
        return;
    cout << t->s << "," << t->d<<endl;
    preorder(t->l);
    preorder(t->r);
}
void avl_tree::postorder(avl *t) {
    if (t == NULL)
        return;
    postorder(t ->l);
    postorder(t ->r);
    cout << t->s << "," << t->d <<endl;
}

int avl_tree::search(string &word) {
    avl *p = r;                                     //Search pointer
    while (p) {
        if (word < p->s) {
            p = p->l;
        } else {
            if (word > p->s)
                p = p->r;
            else {
                return p->d;
            }
        }
    }
    return 0;
}