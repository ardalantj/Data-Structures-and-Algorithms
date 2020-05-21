//
//  main.cpp
//  AVL
//
//  Created by Ardalan TJ on 5/21/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#include <iostream>

struct Node
{
    struct Node *lchild;
    struct Node *rchild;
    int data;
    int height;
}*root = nullptr;

int NodeHeight(struct Node *p)
{
    int hl, hr;
    hl = p && p->lchild ? p->lchild->height:0;
    hr = p && p->rchild ? p->rchild->height:0;
    
    return hl>hr?hl+1:hr+1;
}

int BalanceFactor(struct Node *p)
{
    int hl, hr;
    hl = p && p->lchild ? p->lchild->height:0;
    hr = p && p->rchild ? p->rchild->height:0;
    
    return hl-hr;
}

struct Node* LLRotation(struct Node *p)
{
    struct Node *pl = p->lchild;
    struct Node *plr = pl->rchild;
    
    pl->rchild = p;
    p->lchild = plr;
    p->height = NodeHeight(p);
    pl->height = NodeHeight(pl);
    
    if(root == p)
        root = pl;
    
    return pl;
}

struct Node* RLRotation(struct Node *p)
{
    struct Node *pr = p->rchild;
    struct Node *prl = pr->lchild;
    
    pr->lchild = prl->rchild;
    p->rchild = prl->lchild;
    prl->rchild = pr;
    prl->lchild = p;
    
    pr->height = NodeHeight(pr);
    p->height = NodeHeight(p);
    prl->height = NodeHeight(prl);
    
    if(p == root)
        root = prl;
    
    return prl;
}

struct Node* RRRotation(struct Node *p)
{
    struct Node *pr = p->rchild;
    struct Node *prl = pr->lchild;
    
    pr->lchild = p;
    p->rchild = prl;
    p->height = NodeHeight(p);
    pr->height = NodeHeight(pr);
    
    if(root == p)
        root = pr;
    return pr;
}

struct Node* LRRotation(struct Node *p)
{
    struct Node *pl = p->lchild;
    struct Node *plr = pl->rchild;
    
    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;
    plr->lchild = pl;
    plr->rchild = p;
    
    pl->height = NodeHeight(pl);
    p->height = NodeHeight(p);
    plr->height = NodeHeight(plr);
    
    if(p == root)
        root = plr;
    
    return plr;
}

struct Node* RInsert(struct Node *p, int key)
{
    if(p == nullptr)
    {
        Node *t = new Node();
        t->data = key;
        t->height = 1;
        t->lchild = nullptr;
        t->rchild = nullptr;
        return t;
    }
    if(key < p->data)
        p->lchild = RInsert(p->lchild, key);
    else if(key > p->data)
        p->rchild = RInsert(p->rchild, key);
    
    p->height = NodeHeight(p);
    
    if(BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1)
        return LLRotation(p);
    
    else if(BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1)
        return LRRotation(p);
    
    else if(BalanceFactor(p) == -2 && BalanceFactor(p->lchild) == -1)
        return RRRotation(p);
    
    else if(BalanceFactor(p) == -2 && BalanceFactor(p->lchild) == 1)
        return RLRotation(p);
    
    return p;
}

int main() {
    root = RInsert(root, 50);
    RInsert(root, 10);
    RInsert(root, 20);
    
    return 0;
}
