//
//  main.cpp
//  BST
//
//  Created by Ardalan TJ on 4/27/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#include <iostream>

struct Node
{
    Node *lchild;
    int data;
    Node *rchild;
};
Node *root = nullptr;

void Insert(int key)
{
    Node *t = root;
    Node *r, *p;
    
    if(root == nullptr)
    {
        p = new Node();
        p->data = key;
        p->lchild = p->rchild = nullptr;
        root = p;
        return;
    }
    while(t!= nullptr)
    {
        r = t;
        if(key < t->data)
            t = t->lchild;
        else if(key > t->data)
            t = t->rchild;
        else
            return;
    }
    p = new Node();
    p->data = key;
    p->lchild = p->rchild = nullptr;
    
    if(key < r->data)
        r->lchild = p;
    else
        r->rchild = p;
}

void Inorder(Node *p)
{
    if(p)
    {
        Inorder(p->lchild);
        printf("%d", p->data);
        Inorder(p->rchild);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...

    Insert(10);
    Insert(5);
    Insert(20);
    Insert(8);
    
    Inorder(root);
    printf("\n");
    return 0;
}
