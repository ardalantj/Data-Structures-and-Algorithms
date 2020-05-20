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
    struct Node *lchild;
    struct Node *rchild;
    int data;
}*root = nullptr;

void Insert(int key)
{
    struct Node *t = root;
    struct Node *p;
    struct Node *r = nullptr;
    
// Handle the first node when tree is empty
    if(root == nullptr)
    {
        p = (struct Node *)malloc(sizeof(struct Node));
        p->data = key;
        p->lchild = nullptr;
        p->rchild = nullptr;
        root = p;
        return;
    }
    while(t != nullptr)
    {
        r = t;
        if(key < t->data)
            t = t->lchild;
        else if(key > t->data)
            t = t->rchild;
        else
            return;
    }
    // Create new node
    p = (struct Node *)malloc(sizeof(struct Node));
    p->data = key;
    p->lchild = nullptr;
    p->rchild = nullptr;
    
    if(key < r->data)
        r->lchild = p;
    else
        r->rchild = p;
}

void Inorder(struct Node *p)
{
    if(p)
    {
        Inorder(p->lchild);
        printf("%d ", p->data);
        Inorder(p->rchild);
    }
}

struct Node * Search(int key)
{
    struct Node *t = root;
    while(t != nullptr)
    {
        if(key == t->data)
            return t;
        else if(key < t->data)
            t = t->lchild;
        else
            t = t->rchild;
    }
    return nullptr;
}

int Height(struct Node *p)
{
    int x,y;
    if(p == nullptr)
        return 0;
    x = Height(p->lchild);
    y = Height(p->rchild);
    return x>y?x+1:y+1;
}

struct Node* Inpre(struct Node *p)
{
    while(p && p->rchild != nullptr)
        p = p->rchild;
    return p;
}

struct Node* InSucc(struct Node *p)
{
    while(p && p->lchild != nullptr)
        p = p->lchild;
    return p;
}

struct Node *RInsert(struct Node *p, int key)
{
    struct Node *t = nullptr;
    if(p == nullptr)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = key;
        t->lchild = nullptr;
        t->rchild = nullptr;
        return t;
    }
    if(key < p->data)
       p->lchild = RInsert(p->lchild, key);
    else if(key > p->data)
        p->rchild = RInsert(p->rchild, key);
    return p;
}

struct Node* Delete(struct Node *p, int key)
{
    struct Node *q = nullptr;
    if(p == nullptr)
        return nullptr;
    
    if(p->lchild == nullptr && p->rchild == nullptr)
    {
        if(p == root)
            root == nullptr;
        free(p);
        return nullptr;
    }
    if(key < p->data)
        p->lchild = Delete(p->lchild, key);
    else if(key > p->data)
        p->rchild = Delete(p->rchild, key);
    else
    {
        if(Height(p->lchild) > Height(p->rchild))
        {
            q = Inpre(p->lchild);
            p->data = q->data;
            p->lchild = Delete(p->lchild, q->data);
        }
        else
        {
            q = InSucc(p->rchild);
            p->data = q->data;
            p->rchild = Delete(p->rchild, q->data);
        }
    }
    return p;
}
int main() {
    // insert code here...
    
    struct Node *temp = nullptr;
    root = RInsert(root, 10);
    RInsert(root, 20);
    RInsert(root, 20);
    RInsert(root, 8);
    RInsert(root, 30);
    Delete(root, 20);
    Inorder(root);
    printf("\n");
    
    temp = Search(20);
    if(temp != nullptr)
        printf("Element %d is found\n", temp->data);
    else
        printf("Element is not found\n");
    
    return 0;
}
