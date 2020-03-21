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

//Node *first = nullptr;
//Node *second = nullptr;
//Node *third = nullptr;

class LinkedList
{

private:
    Node *first;
    
public:
    LinkedList(){first = nullptr;}
    LinkedList(int A[], int n);
    ~LinkedList();
    
    void Display();
    void Insert(int index);
    void Create2(int A[], int n);
    int Count();
    int Sum();
    int Max();
    int Rmax();
    Node * Search(int key);
    Node* RSearch(int key);
    void Insert(int index, int x);
    void SortedInsert(int x);
    int Delete(int index);
    bool isSorted();
    void RemoveDuplicate();
    void Reverse();
    void Concat(Node *q);
    int isLoop();
    Node* Merge(Node* h2);
};

LinkedList::LinkedList(int A[], int n)
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

LinkedList::~LinkedList()
{
    Node *p = first;
    while(first)
    {
        first = first->next;
        delete p;
        p = first;
    }
}

void LinkedList::Create2(int A[], int n)
{
    int i;
    Node *temp,*last,*second;
    
    second = new Node;
    second->data = A[0];
    second->next = nullptr;
    last = second;
    
    for(i=1; i<n; i++)
    {
        temp = new Node;
        temp->data = A[i];
        temp->next = nullptr;
        last->next = temp;
        last = temp;
    }
}

void LinkedList::Display()
{
    Node *p = first;
    while(p!=nullptr)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}

int LinkedList::Count()
{
    Node *p = first;
    int length = 0;
    while(p != nullptr)
    {
        length++;
        p = p->next;
    }
    return length;
}

int LinkedList::Sum()
{
    Node *p = first;
    int sum = 0;
    while(p != nullptr)
    {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

int LinkedList::Max()
{
    Node *p = first;
    int max = INT32_MIN;
    while(p != nullptr)
    {
        if(p->data > max)
            max = p->data;
        p = p->next;
    }
    return max;
}

int LinkedList::Rmax()
{
    Node *p = first;
    int x = 0;
    
    if(p == nullptr)
        return INT32_MIN;
    x = Rmax();
    if(x>p->data)
        return x;
    else return p->data;
}

Node* LinkedList::Search(int key)
{
    Node *p = first;
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

Node* LinkedList::RSearch(int key)
{
    Node *p = first;
    if(p == nullptr)
        return nullptr;
    if(key == p->data)
        return p;
    return RSearch(key);
}

void LinkedList::Insert(int index, int x)
{
    Node *p = first;
    Node *t;
    
    if(index < 0 || index > Count())
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

void LinkedList::SortedInsert(int x)
{
    Node *p = first;
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

int LinkedList::Delete(int index)
{
    Node *p = first;
    Node *q = nullptr;
    int x = -1;
    
    if(index < 1 || index > Count())
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

bool LinkedList::isSorted()
{
    Node *p = first;
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

void LinkedList::RemoveDuplicate()
{
    Node *p = first;
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

void LinkedList::Reverse()
{
    Node *p = first;
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

void LinkedList::Concat(Node *q)
{
    Node *p = first;
    while(p->next != nullptr)
    {
        p = p->next;
    }
    p->next = q;
    q = nullptr;
}

Node* LinkedList::Merge(Node* h2)
{
    Node *p = first;
    if (!p)
        return h2;
    if (!h2)
        return p;
  
    // start with the linked list
    // whose head data is the least
    if (p->data < h2->data) {
        p->next = Merge(h2);
        return p;
    }
    else {
        h2->next = Merge(h2->next);
        return h2;
    }
}

int LinkedList::isLoop()
{
    Node *f = first;
    Node *p,*q;
    p = q = f;
    
    do
    {
        p = p->next;
        q = q->next;
        q = q?q->next:q;
    }while(p && q && p!=q);
    
    if(p==q)
        return 1;
    else
        return 0;
}

int main(int argc, const char * argv[]) {
   
    int A[] = {10,20,30,40,50};
    LinkedList l(A,5);
    l.Insert(3,100);
    l.Display();

    return 0;
}
