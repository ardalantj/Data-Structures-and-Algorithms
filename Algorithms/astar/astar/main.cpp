//
//  main.cpp
//  astar
//
//  Created by Ardalan TJ on 4/23/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <iostream>
#include <stack>

#define ROW 9
#define COL 10
using namespace std;

// Creating data type for int, int pair type
typedef pair<int,int> Pair;

// Creating data type for cost, coordinate pair
typedef pair<double, pair<int,int>> pPair;

struct cell
{
// Row and col index of its parents
//  0 <= i <= row-1 & 0 <= j <= col-1
    int parent_i, parent_j;
    // f = g+h
    double f, g, h;
};

// Function to check whether a given cell is valid
bool isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// Function to check whether a given cell is an obstacle or not
bool isUnblocked(int grid[ROW][COL], int row, int col)
{
    // Return true if the cell is unblocked: 1 is unblocked, 0 is blocked
    if(grid[row][col] == 1)
        return true;
    else
        return false;
}

// Function to check whether destination cell has been reached or not
bool isDestination(int row, int col, Pair dest)
{
    if(row == dest.first && col == dest.second)
        return true;
    else
        return false;
}

// Function that calculates the h heuristic
double calculateH(int row, int col, Pair dest)
{
    return (double)sqrt((row - dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second));
}

// Function to reconstruct the traversed path from source to destination
void tracePath(cell cellDetails[ROW][COL], Pair dest)
{
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
    
    stack<Pair> Path;
    while(!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
    {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    
    Path.push(make_pair(row, col));
    while(!Path.empty())
    {
        pair<int,int> p = Path.top();
        Path.pop();
        printf("-> (%d, %d)", p.first, p.second);
    }
    return;
}

void aStarSearch(int grid[ROW][COL], Pair src, Pair dest)
{
    // Check if source is out of range
    if(!isValid(src.first, src.second))
    {
        printf("Source is invalid\n");
        return;
    }
    // Check if destination is out of range
    if(!isValid(dest.first, dest.second))
    {
        printf("Destination is invalid\n");
        return;
    }
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
