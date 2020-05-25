//
//  chain.h
//  Hashing
//
//  Created by Ardalan TJ on 5/25/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#ifndef chain_h
#define chain_h

#include <iostream>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
}*first = nullptr;


void SortedInsert(struct Node **H, int x)
{
    struct Node *t, *q = nullptr, *p = *H;
    
    t = (struct Node*)malloc(sizeof(struct Node));
    t->data = x;
    t->next = nullptr;
    
    if(*H == nullptr)
        *H = t;
    else
    {
        while(p && p->data < x)
        {
            q = p;
            p = p->next;
        }
        if(p == first)
        {
            t->next = first;
            first = t;
        }
        else
        {
            t->next = q->next;
            q->next = t;
        }
    }
}

struct Node *Search(struct Node *p, int key)
{
    while(p != nullptr)
    {
        if(key == p->data)
        {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}


#endif /* chain_h */
