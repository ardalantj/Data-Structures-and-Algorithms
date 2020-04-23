//
//  main.cpp
//  Dijkstra
//
//  Created by Ardalan TJ on 4/1/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//
#include <iostream>
#define INF 999

using namespace std;

int V, cost[100][100], src;
int dist[100];
bool visited[100] = {0};
int parent[100];

void init(){
    for(int i = 0; i < V; i++){
        parent[i] = i;
        dist[i] = INF;
    }
    dist[src] = 0;
}

int getNearest()
{
    int minValue = INF;
    int minnode = 0;
    for(int i = 0; i < V; i++)
    {
        if(!visited[i] && dist[i] < minValue){
            minValue = dist[i];
            minnode = i;
        }
    }
    return minnode;
}

void dikjstra()
{
    for(int i = 0; i < V-1; i++)
    {
        int nearest = getNearest();
        visited[nearest] = true;
        
        for(int adj = 0; adj < V; adj++)
        {
            if(cost[nearest][adj] != INF && dist[adj] > dist[nearest] + cost[nearest][adj]){
                dist[adj] = dist[nearest] + cost[nearest][adj];
                parent[adj] = nearest;
            }
        }
    }
}

void Display()
{
    cout << "Node:\t\t\tCost :\t\t\tPath";
    
    for(int i = 0; i < V; i++)
    {
        cout <<i<<"\t\t\t" << dist[i]<<"\t\t\t"<<" ";
        cout << i <<" ";
        int parnode = parent[i];
        
        while(parnode != src){
            cout << " <- " << parnode << " ";
            parnode = parent[parnode];
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    cin >> V;
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            cin >> cost[i][j];
        }
    }
    
    cin >> src;
    init();
    dikjstra();
    Display();
}
