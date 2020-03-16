//
//  main.cpp
//  Linked List
//
//  Created by Ardalan TJ on 3/12/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#include <iostream>

class Node
{
public:
    int data;
    Node *next;
};

Node *first = nullptr;

void Create(int A[], int n)
{
    int i;
    Node *temp,*last;
    
    first = new Node;
    first->data = A[0];
    first->next = nullptr;
    last = first;
    
    for(i=1; i<n; i++)
    {
        temp = new Node;
        temp->data = A[i];
        temp->next = nullptr;
        last->next = temp;
        last = temp;
    }
}

void Display(Node *p)
{
    while(p!=nullptr)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}

int Count(Node *p)
{
    int length = 0;
    while(p != nullptr)
    {
        length++;
        p = p->next;
    }
    return length;
}

int Sum(Node *p)
{
    int sum = 0;
    while(p != nullptr)
    {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

int Max(Node *p)
{
    int max = INT32_MIN;
    while(p != nullptr)
    {
        if(p->data > max)
            max = p->data;
        p = p->next;
    }
    return max;
}

int Rmax(Node *p)
{
    int x = 0;
    
    if(p == nullptr)
        return INT32_MIN;
    x = Rmax(p->next);
    if(x>p->data)
        return x;
    else return p->data;
}

Node* Search(Node *p, int key)
{
    Node *q = nullptr;
    
    while(p != nullptr)
    {
        if(key == p->data)
        {
            q->next = p->next;
            p->next = first;
            first = p;
            return p;
        }
        q = p;
        p = p->next;
    }
    return nullptr;
}

Node* RSearch(Node *p, int key)
{
    if(p == nullptr)
        return nullptr;
    if(key == p->data)
        return p;
    return RSearch(p->next, key);
}

void Insert(Node *p, int index, int x)
{
    Node *t;
    
    if(index < 0 || index > Count(p))
        return;
    t = new Node();
    t->data = x;

    if(index == 0)
    {
        t->next = first;
        first = t;
    }
    else
    {
        for(int i = 1; i < index-1; i++)
            p = p->next;
        t->next = p->next;
        p->next = t;
    }
}

void SortedInsert(Node *p, int x)
{
    Node *t, *q = nullptr;
    t = new Node();
    t->data=x;
    t->next=nullptr;
    
    if(first == nullptr)
        first = t;
    else
    {
        while(p != nullptr && p->data < x)
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

int Delete(Node *p, int index)
{
    Node *q = nullptr;
    int x = -1;
    
    if(index < 1 || index > Count(p))
        return -1;
    if(index == 1)
    {
        q = first;
        x = first->data;
        first = first->next;
        delete q;
        return x;
    }
    else
    {
        for(int i = 0; i < index-1; i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        x = p->data;
        delete p;
        return x;
    }
}

bool isSorted(Node *p)
{
    int x = INT32_MIN;
    
    while(p != nullptr)
    {
       if(p->data < x)
           return false;
        x = p->data;
        p = p->next;
    }
    return true;
}

void RemoveDuplicate(Node *p)
{
    Node *q = p->next;
    while(q != nullptr)
    {
        if(p->data != q->data)
        {
            p = q;
            q = q->next;
        }
        else
        {
            p->next = q->next;
            delete q;
            q = p->next;
        }
    }
}

void Reverse(Node *p)
{
    Node *q = nullptr;
    Node *r = nullptr;
    
    while(p != nullptr)
    {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    first = q;
}

int main(int argc, const char * argv[]) {
   
    int A[] = {10,20,20,20,30,40,50};
    Create(A,7);
    //Display(first);
   // printf("Length is %d", Count(first));
    //SortedInsert(first,2);
    //Delete(first,4);
    RemoveDuplicate(first);
    Display(first);
    
    return 0;
}
