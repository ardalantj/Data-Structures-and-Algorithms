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

int main(int argc, const char * argv[]) {
   
    int A[] = {3,5,7,10,15};
    Create(A,5);
    Display(first);
    
    return 0;
}
