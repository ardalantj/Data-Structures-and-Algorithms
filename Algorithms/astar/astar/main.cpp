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
#include <float.h>
#include <set>

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

// Implements the astar algorithm. It finds the shortest path from a src to dest
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
    // Check if either of the source or destination is blocked
    if(!isUnblocked(grid, src.first, src.second) || !isUnblocked(grid, dest.first, dest.second))
    {
        printf("Source or destination is blocked!");
        return;
    }
    // Check if the destination cell is the same as the source cell
    if(isDestination(src.first, src.second, dest))
    {
        printf("We are already at the destination\n");
        return;
    }
    // Create a closed list and initialize it to false
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));
    
    // Declare 2d array of structures to hold cell details
    cell cellDetails[ROW][COL];
    
    int i,j;
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }
    // Initialize the parameters of the starting node
    i = src.first;
    j = src.second;
    
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    
    // Create an open list <f,<i,j>> where f = g + h, initialize the starting
    // cell with f = 0
    set<pPair> openList;
    openList.insert(make_pair(0.0, make_pair(i, j)));
    
    bool foundDest = false;
    
    while(!openList.empty())
    {
        pPair p = *openList.begin();
        
        //Remove the vertex from the open list
        openList.erase(openList.begin());
        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
        
        // store g, h, and f of the successors
        double gNew, fNew, hNew;
        
        // Only process this cell if this is a valid one
        if(isValid(i-1, j) == true)
        {
            // If the destination is the same as the successor cell
            if(isDestination(i-1, j, dest) == true)
            {
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                printf("The destination is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed list or if it is blocked, then ignore it, else do:
            else if(closedList[i-1][j] == false && isUnblocked(grid, i-1, j) == true)
            {
                gNew = cellDetails[i-1][j].g + 1.0;
                hNew = calculateH(i-1, j, dest);
                fNew = gNew + hNew;
                
            if(cellDetails[i-1][j].f == FLT_MAX || cellDetails[i-1][j].f > fNew)
            {
                openList.insert(make_pair(fNew, make_pair(i-1, j)));
                cellDetails[i-1][j].f = fNew;
                cellDetails[i-1][j].g = gNew;
                cellDetails[i-1][j].h = hNew;
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
            }
                
            }
        }
        
        // Only process this cell if this is a valid one
               if(isValid(i+1, j) == true)
               {
                   // If the destination is the same as the successor cell
                   if(isDestination(i+1, j, dest) == true)
                   {
                       cellDetails[i+1][j].parent_i = i;
                       cellDetails[i+1][j].parent_j = j;
                       printf("The destination is found\n");
                       tracePath(cellDetails, dest);
                       foundDest = true;
                       return;
                   }
                   // If the successor is already on the closed list or if it is blocked, then ignore it, else do:
                   else if(closedList[i+1][j] == false && isUnblocked(grid, i+1, j) == true)
                   {
                       gNew = cellDetails[i+1][j].g + 1.0;
                       hNew = calculateH(i+1, j, dest);
                       fNew = gNew + hNew;
                       
                   if(cellDetails[i+1][j].f == FLT_MAX || cellDetails[i+1][j].f > fNew)
                   {
                       openList.insert(make_pair(fNew, make_pair(i+1, j)));
                       cellDetails[i+1][j].f = fNew;
                       cellDetails[i+1][j].g = gNew;
                       cellDetails[i+1][j].h = hNew;
                       cellDetails[i+1][j].parent_i = i;
                       cellDetails[i+1][j].parent_j = j;
                   }
                       
                   }
               }
        
                //----------- 3rd Successor (East) ------------
        
              // Only process this cell if this is a valid one
                if (isValid (i, j+1) == true)
                {
                  // If the destination cell is the same as the
                  // current successor
                  if (isDestination(i, j+1, dest) == true)
                  {
                      // Set the Parent of the destination cell
                      cellDetails[i][j+1].parent_i = i;
                      cellDetails[i][j+1].parent_j = j;
                      printf("The destination cell is found\n");
                      tracePath(cellDetails, dest);
                      foundDest = true;
                      return;
                  }
        
                  // If the successor is already on the closed
                  // list or if it is blocked, then ignore it.
                  // Else do the following
                  else if (closedList[i][j+1] == false &&
                           isUnblocked(grid, i, j+1) == true)
                  {
                      gNew = cellDetails[i][j].g + 1.0;
                      hNew = calculateH(i, j+1, dest);
                      fNew = gNew + hNew;
        
                      // If it isn’t on the open list, add it to
                      // the open list. Make the current square
                      // the parent of this square. Record the
                      // f, g, and h costs of the square cell
                      //                OR
                      // If it is on the open list already, check
                      // to see if this path to that square is better,
                      // using 'f' cost as the measure.
                      if (cellDetails[i][j+1].f == FLT_MAX ||
                              cellDetails[i][j+1].f > fNew)
                      {
                          openList.insert( make_pair(fNew,
                                              make_pair (i, j+1)));
        
                          // Update the details of this cell
                          cellDetails[i][j+1].f = fNew;
                          cellDetails[i][j+1].g = gNew;
                          cellDetails[i][j+1].h = hNew;
                          cellDetails[i][j+1].parent_i = i;
                          cellDetails[i][j+1].parent_j = j;
                      }
                  }
              }
        
                //----------- 4th Successor (West) ------------
         
               // Only process this cell if this is a valid one
                    if (isValid(i, j-1) == true)
                    {
                   // If the destination cell is the same as the
                   // current successor
                   if (isDestination(i, j-1, dest) == true)
                   {
                       // Set the Parent of the destination cell
                       cellDetails[i][j-1].parent_i = i;
                       cellDetails[i][j-1].parent_j = j;
                       printf("The destination cell is found\n");
                       tracePath(cellDetails, dest);
                       foundDest = true;
                       return;
                   }
         
                   // If the successor is already on the closed
                   // list or if it is blocked, then ignore it.
                   // Else do the following
                   else if (closedList[i][j-1] == false &&
                            isUnblocked(grid, i, j-1) == true)
                   {
                       gNew = cellDetails[i][j].g + 1.0;
                       hNew = calculateH(i, j-1, dest);
                       fNew = gNew + hNew;
         
                       // If it isn’t on the open list, add it to
                       // the open list. Make the current square
                       // the parent of this square. Record the
                       // f, g, and h costs of the square cell
                       //                OR
                       // If it is on the open list already, check
                       // to see if this path to that square is better,
                       // using 'f' cost as the measure.
                       if (cellDetails[i][j-1].f == FLT_MAX ||
                               cellDetails[i][j-1].f > fNew)
                       {
                           openList.insert( make_pair (fNew,
                                                 make_pair (i, j-1)));
         
                           // Update the details of this cell
                           cellDetails[i][j-1].f = fNew;
                           cellDetails[i][j-1].g = gNew;
                           cellDetails[i][j-1].h = hNew;
                           cellDetails[i][j-1].parent_i = i;
                           cellDetails[i][j-1].parent_j = j;
                       }
                   }
               }
                //----------- 5th Successor (North-East) ------------
         
               // Only process this cell if this is a valid one
                    if (isValid(i-1, j+1) == true)
                    {
                   // If the destination cell is the same as the
                   // current successor
                   if (isDestination(i-1, j+1, dest) == true)
                   {
                       // Set the Parent of the destination cell
                       cellDetails[i-1][j+1].parent_i = i;
                       cellDetails[i-1][j+1].parent_j = j;
                       printf ("The destination cell is found\n");
                       tracePath (cellDetails, dest);
                       foundDest = true;
                       return;
                   }
         
                   // If the successor is already on the closed
                   // list or if it is blocked, then ignore it.
                   // Else do the following
                   else if (closedList[i-1][j+1] == false &&
                            isUnblocked(grid, i-1, j+1) == true)
                   {
                       gNew = cellDetails[i][j].g + 1.414;
                       hNew = calculateH(i-1, j+1, dest);
                       fNew = gNew + hNew;
         
                       // If it isn’t on the open list, add it to
                       // the open list. Make the current square
                       // the parent of this square. Record the
                       // f, g, and h costs of the square cell
                       //                OR
                       // If it is on the open list already, check
                       // to see if this path to that square is better,
                       // using 'f' cost as the measure.
                       if (cellDetails[i-1][j+1].f == FLT_MAX ||
                               cellDetails[i-1][j+1].f > fNew)
                       {
                           openList.insert( make_pair (fNew,
                                           make_pair(i-1, j+1)));
         
                           // Update the details of this cell
                           cellDetails[i-1][j+1].f = fNew;
                           cellDetails[i-1][j+1].g = gNew;
                           cellDetails[i-1][j+1].h = hNew;
                           cellDetails[i-1][j+1].parent_i = i;
                           cellDetails[i-1][j+1].parent_j = j;
                       }
                   }
               }
                //----------- 6th Successor (North-West) ------------
        
              // Only process this cell if this is a valid one
                if (isValid (i-1, j-1) == true)
                {
                  // If the destination cell is the same as the
                  // current successor
                  if (isDestination (i-1, j-1, dest) == true)
                  {
                      // Set the Parent of the destination cell
                      cellDetails[i-1][j-1].parent_i = i;
                      cellDetails[i-1][j-1].parent_j = j;
                      printf ("The destination cell is found\n");
                      tracePath (cellDetails, dest);
                      foundDest = true;
                      return;
                  }
        
                  // If the successor is already on the closed
                  // list or if it is blocked, then ignore it.
                  // Else do the following
                  else if (closedList[i-1][j-1] == false &&
                           isUnblocked(grid, i-1, j-1) == true)
                  {
                      gNew = cellDetails[i][j].g + 1.414;
                      hNew = calculateH(i-1, j-1, dest);
                      fNew = gNew + hNew;
        
                      // If it isn’t on the open list, add it to
                      // the open list. Make the current square
                      // the parent of this square. Record the
                      // f, g, and h costs of the square cell
                      //                OR
                      // If it is on the open list already, check
                      // to see if this path to that square is better,
                      // using 'f' cost as the measure.
                      if (cellDetails[i-1][j-1].f == FLT_MAX ||
                              cellDetails[i-1][j-1].f > fNew)
                      {
                          openList.insert( make_pair (fNew, make_pair (i-1, j-1)));
                          // Update the details of this cell
                          cellDetails[i-1][j-1].f = fNew;
                          cellDetails[i-1][j-1].g = gNew;
                          cellDetails[i-1][j-1].h = hNew;
                          cellDetails[i-1][j-1].parent_i = i;
                          cellDetails[i-1][j-1].parent_j = j;
                      }
                  }
              }
        
                //----------- 7th Successor (South-East) ------------
        
              // Only process this cell if this is a valid one
                if (isValid(i+1, j+1) == true)
                {
                  // If the destination cell is the same as the
                  // current successor
                  if (isDestination(i+1, j+1, dest) == true)
                  {
                      // Set the Parent of the destination cell
                      cellDetails[i+1][j+1].parent_i = i;
                      cellDetails[i+1][j+1].parent_j = j;
                      printf ("The destination cell is found\n");
                      tracePath (cellDetails, dest);
                      foundDest = true;
                      return;
                  }
        
                  // If the successor is already on the closed
                  // list or if it is blocked, then ignore it.
                  // Else do the following
                  else if (closedList[i+1][j+1] == false &&
                           isUnblocked(grid, i+1, j+1) == true)
                  {
                      gNew = cellDetails[i][j].g + 1.414;
                      hNew = calculateH(i+1, j+1, dest);
                      fNew = gNew + hNew;
        
                      // If it isn’t on the open list, add it to
                      // the open list. Make the current square
                      // the parent of this square. Record the
                      // f, g, and h costs of the square cell
                      //                OR
                      // If it is on the open list already, check
                      // to see if this path to that square is better,
                      // using 'f' cost as the measure.
                      if (cellDetails[i+1][j+1].f == FLT_MAX ||
                              cellDetails[i+1][j+1].f > fNew)
                      {
                          openList.insert(make_pair(fNew,
                                              make_pair (i+1, j+1)));
        
                          // Update the details of this cell
                          cellDetails[i+1][j+1].f = fNew;
                          cellDetails[i+1][j+1].g = gNew;
                          cellDetails[i+1][j+1].h = hNew;
                          cellDetails[i+1][j+1].parent_i = i;
                          cellDetails[i+1][j+1].parent_j = j;
                      }
                  }
              }
        
                //----------- 8th Successor (South-West) ------------
        
              // Only process this cell if this is a valid one
              if (isValid (i+1, j-1) == true)
              {
                  // If the destination cell is the same as the
                  // current successor
                  if (isDestination(i+1, j-1, dest) == true)
                  {
                      // Set the Parent of the destination cell
                      cellDetails[i+1][j-1].parent_i = i;
                      cellDetails[i+1][j-1].parent_j = j;
                      printf("The destination cell is found\n");
                      tracePath(cellDetails, dest);
                      foundDest = true;
                      return;
                  }
        
                  // If the successor is already on the closed
                  // list or if it is blocked, then ignore it.
                  // Else do the following
                  else if (closedList[i+1][j-1] == false &&
                           isUnblocked(grid, i+1, j-1) == true)
                  {
                      gNew = cellDetails[i][j].g + 1.414;
                      hNew = calculateH(i+1, j-1, dest);
                      fNew = gNew + hNew;
        
                      // If it isn’t on the open list, add it to
                      // the open list. Make the current square
                      // the parent of this square. Record the
                      // f, g, and h costs of the square cell
                      //                OR
                      // If it is on the open list already, check
                      // to see if this path to that square is better,
                      // using 'f' cost as the measure.
                      if (cellDetails[i+1][j-1].f == FLT_MAX ||
                              cellDetails[i+1][j-1].f > fNew)
                      {
                          openList.insert(make_pair(fNew,
                                              make_pair(i+1, j-1)));
        
                          // Update the details of this cell
                          cellDetails[i+1][j-1].f = fNew;
                          cellDetails[i+1][j-1].g = gNew;
                          cellDetails[i+1][j-1].h = hNew;
                          cellDetails[i+1][j-1].parent_i = i;
                          cellDetails[i+1][j-1].parent_j = j;
                      }
                    }
                }
            }
    if(foundDest == false)
        printf("Failed to find the destination cell\n");
    return;
}

int main() {
    // insert code here...
    /* Description of the Grid-
        1--> The cell is not blocked
        0--> The cell is blocked    */
       int grid[ROW][COL] =
       {
           { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
           { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
           { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
           { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
           { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
           { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
           { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
       };
    
    Pair src = make_pair(8,0);
    Pair dest = make_pair(0,0);
    aStarSearch(grid, src, dest);
    
    return 0;
}
