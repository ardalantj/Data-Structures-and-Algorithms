//
//  main.cpp
//  Hash_linear_probe
//
//  Created by Ardalan TJ on 5/25/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#include <iostream>
#define SIZE 10

int hash(int key)
{
    return key % SIZE;
}

int probe(int H[], int key)
{
    int index = hash(key);
    int i = 0;
    while(H[(index + i)] % SIZE != 0)
    {
        i++;
    }
    return (index + i) % SIZE;
}

void Insert(int H[], int key)
{
    int index = hash(key);
    
    if(H[index] != 0)
        index = probe(H, key);
    H[index] = key;
}

int Search(int H[], int key)
{
    int index = hash(key);
    int i = 0;
    
    while((H[index + i]) % SIZE != 0)
    {
        i++;
    }
    return (index + i) % SIZE;
}

int main() {
    // insert code here...
    int HT[10] = {0};
    Insert(HT, 12);
    Insert(HT, 25);
    Insert(HT, 35);
    Insert(HT, 26);
    
    printf("\nKey found at %d\n", Search(HT, 25));
    return 0;
}
