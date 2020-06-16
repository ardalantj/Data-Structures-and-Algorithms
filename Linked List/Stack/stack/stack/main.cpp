//
//  main.cpp
//  stack
//
//  Created by Ardalan TJ on 6/15/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#include <iostream>

class Node{
public:
    int data;
    Node *next;
};

class Stack
{
private:
    Node *top;
    
public:
    Stack(){top = nullptr;}
    void push(int x);
    int pop();
    void Display();
};

void Stack::push(int x)
{
    Node *t = new Node;
    if(t == nullptr)
        std::cout << "Stack is full";
    else
    {
        t->data = x;
        t->next = top;
        top = t;
    }
}

int Stack::pop()
{
    int x = -1;
    if(top == nullptr)
        std::cout << "Stack is Empty\n";
    else
    {
        x = top->data;
        Node *t = top;
        top = top->next;
        delete t;
    }
    return x;
}

void Stack::Display()
{
    Node *p = top;
    while(p!= nullptr)
    {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout<<std::endl;
}

int main(int argc, const char * argv[]) {
    Stack stk;
    stk.push(10);
    stk.push(20);
    stk.push(30);
    
    stk.Display();
}
