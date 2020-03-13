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

int count(Node *p)
{
    int length = 0;
    while(p != nullptr)
    {
        length++;
        p = p->next;
    }
    return length;
}

int sum(Node *p)
{
    int sum = 0;
    while(p != nullptr)
    {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

int max(Node *p)
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

int main(int argc, const char * argv[]) {
   
    int A[] = {3,5,7,10,15};
    Create(A,5);
    Display(first);
    printf("Length is %d", count(first));
    
    return 0;
}
