/* 
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze=NULL;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
  
   mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS  
     
   if (mymaze == 0) {
      cout << "Error, input format incorrect." << endl;
      return 1;
   }
  
	 //================================
   // When working on Checkpoint 3, you will call maze_search here.
   // But for Checkpoint 1, just assume we found the path.
  
   result = maze_search(mymaze, rows, cols); // <--- TASK: CHANGE THIS
	
	
   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

	 //================================
   // ADD CODE BELOW
   // to delete all memory that read_maze allocated
  
  for(int i=0; i<rows; i++){
    delete[] mymaze[i];
  }
  delete[] mymaze;
  
  
  
   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
  // *** You complete ****
  
  
  Location **predecessor = new Location*[rows];
  for(int i=0; i<rows; i++){
    predecessor[i] = new Location[cols];
    for(int j=0; j<cols;j++){
      predecessor[i][j].row = 0;
    }
  }
  
  int** check = new int*[rows];
  for(int i=0; i<rows; i++){
    check[i] = new int[cols];
    for(int j=0; j<cols;j++){
      check[i][j] = 0;
    }
  }
  
  Location start;
  Location finish;
  Location spot;
  Queue queue(rows*cols);
  
  start.row = -15;
  finish.row = -15;
  int starts = 0;
  int finishes = 0;
  
  //find the start and find the end
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols;j++){
      if(maze[i][j]=='S'){
        start.row = i;
        start.col = j;
        starts++;
      }
      if(maze[i][j]=='F'){
        finish.row = i;
        finish.col = j;
        finishes++;
      }
    }
  }
  
  //if there is no s or f
  if(start.row == -15 || finish.row == -15){ 
    for(int i=0; i<rows; i++){
      delete[] predecessor[i];
      delete[] check[i];
    }
    delete[] predecessor;
    delete[] check;
    return -1;
  }
  //more than 1 f or s
  if(starts > 1 || finishes > 1){ 
    for(int i=0; i<rows; i++){
      delete[] predecessor[i];
      delete[] check[i];
    }
    delete[] predecessor;
    delete[] check;
    return -1;
  }
  
  //bfs
  queue.add_to_back(start);
  while(!queue.is_empty()){
    spot = queue.remove_from_front();
    
    
    //check to see if finished
    if(maze[spot.row][spot.col]=='F'){
      //cout << "hey";
      while(spot.row>=0){
        spot = predecessor[spot.row][spot.col];
        if( (spot.row == start.row) && (spot.col == start.col) ){
          for(int i=0; i<rows; i++){
            delete[] predecessor[i];
            delete[] check[i];
          }
          delete[] predecessor;
          delete[] check;
          return 1;
        }
        maze[spot.row][spot.col] = '*';
      }
    }
        
    
    //up
    if(spot.row-1 >= 0){ //in bounds
      if( (maze[spot.row-1][spot.col] == '.' || maze[spot.row-1][spot.col] == 'F') && 
          (check[spot.row-1][spot.col]==0) ){
        //cout << spot.row << spot.col << maze[spot.row-1][spot.col]<<"u "; 
        check[spot.row-1][spot.col]=1;
        Location temp;
        temp.row = spot.row-1;
        temp.col = spot.col;
        queue.add_to_back(temp);
        predecessor[temp.row][temp.col] = spot;
      }    
    }

    //down
    if(spot.row+1 < rows){ //in bounds
      if( (maze[spot.row+1][spot.col] == '.' || maze[spot.row+1][spot.col] == 'F') && 
          (check[spot.row+1][spot.col]==0) ){
        //cout << spot.row << spot.col << maze[spot.row+1][spot.col]<<"d "; 
        check[spot.row+1][spot.col]=1;
        Location temp;
        temp.row = spot.row+1;
        temp.col = spot.col;
        queue.add_to_back(temp);
        predecessor[temp.row][temp.col] = spot;
      }    
    }
    
    //left
    if(spot.col-1 >= 0){ //in bounds
      if( (maze[spot.row][spot.col-1] == '.' || maze[spot.row][spot.col-1] == 'F') && 
          (check[spot.row][spot.col-1]==0) ){
        //cout << spot.row << spot.col << maze[spot.row][spot.col-1]<<"l "; 
        check[spot.row][spot.col-1]=1;
        Location temp;
        temp.row = spot.row;
        temp.col = spot.col-1;
        queue.add_to_back(temp);
        predecessor[temp.row][temp.col] = spot;
      }    
    }
    
    //right
    if(spot.col+1 < cols){ //in bounds
      if( (maze[spot.row][spot.col+1] == '.' || maze[spot.row][spot.col+1] == 'F') && 
          (check[spot.row][spot.col+1]==0) ){
        //cout << spot.row << spot.col << maze[spot.row][spot.col+1]<<"r ";
        check[spot.row][spot.col+1]=1;
        Location temp;
        temp.row = spot.row;
        temp.col = spot.col+1;
        queue.add_to_back(temp);
        predecessor[temp.row][temp.col] = spot;
      }    
    }
    
  }
  
  //queue is empty and finish is never found?
  return 0; // DELETE this stub, it's just for Checkpoint 1 to compile.
}
