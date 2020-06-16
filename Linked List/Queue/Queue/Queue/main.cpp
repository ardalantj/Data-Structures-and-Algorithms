//
//  main.cpp
//  Queue
//
//  Created by Ardalan TJ on 6/15/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//
#include <iostream>
using namespace std;

class Queue
{
private:
    int front;
    int rear;
    int size;
    int *Q;
public:
    Queue(){front = rear = -1; size = 10; Q = new int[size];}
    Queue(int size){front = rear = -1; this->size = size; Q = new int[size];}
    void enqueue(int x);
    int dequeue();
    void Display();
};

void Queue::enqueue(int x)
{
    if(rear == size - 1)
        printf("Full!");
    else
    {
        rear++;
        Q[rear] = x;
    }
}

int Queue::dequeue()
{
    int x = -1;
    if(front == rear)
        printf("Empty!");
    else
    {
        x = Q[front + 1];
        front++;
    }
    return x;
}

void Queue::Display()
{
    for(int i = front+1; i<=rear; i++)
        printf("%d ", Q[i]);
    printf("\n");
}

int main(int argc, const char * argv[]) {
    Queue q(5);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.Display();
}
