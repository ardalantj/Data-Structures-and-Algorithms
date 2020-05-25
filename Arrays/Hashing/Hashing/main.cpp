//
//  main.cpp
//  Hashing
//
//  Created by Ardalan TJ on 5/24/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#include <iostream>
#include "chain.h"

int hash(int key)
{
    return key % 10;
}

void Insert(struct Node *H[], int key)
{
    int index = hash(key);
    SortedInsert(&H[index],key);
}

int main() {
    
    struct Node *HT[10];
    int i;
    struct Node *temp;
    
    for(i = 0; i < 10; i++)
        HT[i] = nullptr;
    
    Insert(HT, 12);
    Insert(HT, 32);
    Insert(HT, 42);
    temp = Search(HT[hash(12)], 12);
    
    printf("%d ", temp->data);
    
    return 0;
}
