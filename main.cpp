/* C/C++ program to solve Rat in a Maze problem using
   backtracking */
#include<stdio.h>
#include <iostream>

// Maze size
#define MazeSize 12
#define stepPercent 5

int generation=0;

int solution[MazeSize][MazeSize];

bool solveMazeUtil(int maze[MazeSize][MazeSize], int x, int y, int sol[MazeSize][MazeSize]);

/* A utility function to print solution matrix sol[N][N] */
void printMazeToConsole(int sol[MazeSize][MazeSize])
{
    for (int i = 0; i < MazeSize; i++)
    {
        for (int j = 0; j < MazeSize; j++)
            printf(" %d ", sol[i][j]);
        printf("\n");
    }
}

void copyMaze(int from[MazeSize][MazeSize], int to[MazeSize][MazeSize])
{
    for(int i=0;i<MazeSize;++i){
        for(int j=0;j<MazeSize;++j){
            to[i][j]=from[i][j];
        }
    }
}

/* A utility function to check if x,y is valid index for N*N maze */
bool isSafe(int maze[MazeSize][MazeSize], int x, int y)
{
    // if (x,y outside maze) return false
    if(x >= 0 && x < MazeSize && y >= 0 && y < MazeSize && maze[x][y] == 1)
        return true;

    return false;
}

/* This function solves the Maze problem using Backtracking.  It mainly
   uses solveMazeUtil() to solve the problem. It returns false if no
   path is possible, otherwise return true and prints the path in the
   form of 1s. Please note that there may be more than one solutions,
   this function prints one of the feasible solutions.*/
bool solveMaze(int maze[MazeSize][MazeSize])
{
    int sol[MazeSize][MazeSize];
    for (int i = 0; i < MazeSize; ++i) {
        for (int j = 0; j < MazeSize; ++j) {
            sol[i][j]=0;
        }
    }

    if(solveMazeUtil(maze, 0, 0, sol) == false)
    {
        generation++;
        return false;
    }

//    std::cout<<std::endl;
//    printSolution(sol);
//    std::cout<<std::endl;

    copyMaze(sol,solution);


    return true;
}



/* A recursive utility function to solve Maze problem */
bool solveMazeUtil(int maze[MazeSize][MazeSize], int x, int y, int sol[MazeSize][MazeSize])
{
    // if (x,y is goal) return true
    if(x == MazeSize-1 && y == MazeSize-1)
    {
        sol[x][y] = 1;
        return true;
    }

    // Check if maze[x][y] is valid
    if(isSafe(maze, x, y) == true)
    {
        // mark x,y as part of solution path
        sol[x][y] = 1;

        /* Move forward in x direction */
        if (solveMazeUtil(maze, x+1, y, sol) == true)
            return true;

        /* If moving in x direction doesn't give solution then
           Move down in y direction  */
        if (solveMazeUtil(maze, x, y+1, sol) == true)
            return true;

        /* If none of the above movements work then BACKTRACK:
            unmark x,y as part of solution path */
        sol[x][y] = 0;
        return false;
    }

    return false;
}

void generateMaze(int maze[MazeSize][MazeSize])
{

    srand(time(NULL));



        int step;


        do {
            for (int i = 0; i < MazeSize; ++i) {

                for (int j = 0; j < MazeSize; ++j) {


                    step = rand() % 10 + 1;
                    if (step <= stepPercent) {
                        maze[i][j] = 0;
                    } else { maze[i][j] = 1; }


                }
            }

            maze[0][0] = 1;
            maze[MazeSize - 1][MazeSize - 1] = 1;

        }while(!solveMaze(maze));


}

// driver program to test above function
int main()
{
    int maze[MazeSize][MazeSize];
    generateMaze(maze);
    printMazeToConsole(maze);
    std::cout<<"|"<<generation<<"|";
    std::cout<<"generated"<<std::endl<<std::endl;

    std::cout<<"The path:"<<std::endl;
    printMazeToConsole(solution);

    solveMaze(maze);
    return 0;
}