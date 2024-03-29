/*
 * I found this MP to be quite challenging in terms of reading from the input file as I had to spend
 * a lot of time going through the lecture sides to write the correct syntax. In the functions, I implemented
 * the first function by splitting it up into two parts. In the first part, I wrote the code that properly
 * creates the maze object and then allocates memory appropriately for it. I was also a bit shaky
 * on how malloc works so I referred to the slides very heavily for this part of the MP as well. The second
 * part of my implementation focused on filling the maze with the appropriate values listed in the input
 * file by looping through the maze and matching the corresponding parts of the maze in the input file
 * to my maze object. For the second function, I freed the memory which was taken up by the maze object
 * and the cells within it with help from the slides as well as I wasn't sure how to free the memory for
 * the cell objects initially. I also learned that you need to set the objects to NULL once you free their 
 * memory. For the third function, I simply looped through my maze object and printed the corresponding
 * ASCII values. For the final function, I followed the algorithm given as well as saw an issue when I would
 * compile and run my code where S would change to a star. To fix this, I custom changed the start back to S
 * after I recursively found the solution in order to fix this at the end and give the proper solution. Overall
 * the MP was able to bring together a lot of new topics we learned in class so I thought that it was very
 * helpful in that aspect.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    /*
     * ----------------------
     * MEMORY ALLOCATION PART 
     * ----------------------
     */
    int rows, cols, i, j;
    //begin file IO 
    FILE * myfile = fopen(fileName, "r");
    fscanf(myfile, "%d %d", &cols, &rows);
    //create maze object and initialize height and width attributes
    maze_t * myMaze = malloc(sizeof(maze_t));
    myMaze -> height = rows;
    myMaze -> width = cols;
    //allocate memory for each group of cells in a row as a pointer
    myMaze -> cells = (char **) malloc(rows * sizeof(char *));
    //loop through array of pointers and allocate memory for selected number of character cells for each pointer
    for(i = 0; i < rows; i++){
        myMaze -> cells[i] =  (char *) malloc(cols * sizeof(char));
    }

    /*
     * -----------------
     * FILLING MAZE PART 
     * -----------------
     */
    //loop through entire maze
    char charIn;
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            //get a character
            charIn = fgetc(myfile);
            //if start or end mark it and check if its in bounds
            if(charIn == 'S' && j >= 0){
                myMaze -> startRow = i;
                myMaze -> startColumn = j;
            }
            if(charIn == 'E' && j >= 0){
                myMaze -> endRow = i;
                myMaze -> endColumn = j;
            }
            /*
             * if its not a newline, then go ahead and store it. 
             * if it is a newline, go back to the previous cell since newline is an 
             * invalid character to be filled for that cell.
             */
            if(charIn != '\n'){
                myMaze -> cells[i][j] = charIn;
            } else {
                j--;
            }
        }
    }

    fclose(myfile);

    return myMaze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    //loop through rows of maze freeing pointers of rows
    for(i = 0; i < maze -> height; i++){
        free(maze -> cells[i]);
    }
    //free cells and set to null
    free(maze -> cells);
    maze -> cells = NULL;
    //free maze and set to null
    free(maze);
    maze = NULL;
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i, j;
    int rows = maze -> height;
    int cols = maze -> width;

    //print columns and rows and then loop through maze printing each character
    //print a newline after each ROW 
    // printf("%d %d", cols, rows);
    // printf("\n");
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            char outputChar = maze -> cells[i][j];
            printf("%c", outputChar);
        }
        printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    int rowBounds = maze -> height;
    int colBounds = maze -> width; 
    int endRow = maze -> endRow;
    int endCol = maze -> endColumn;
    int startRow = maze -> startRow;
    int startCol = maze -> startColumn; 

    //check if in bounds
    if(row < 0 || row >= rowBounds || col < 0 || col >= colBounds){
        return 0;
    }

    //get current cell value
    char charCheck = maze -> cells[row][col];

    //check if cell value isn't empty space
    if(charCheck == '%' || charCheck == '*' || charCheck == '~'){
        return 0;
    }

    //check if reached end and set beginning to S because code below sets S to a *
    if(row == endRow && col == endCol){
        maze -> cells[startRow][startCol] = 'S';
        return 1;
    }

    //set as part of solution
    if(maze -> cells[row][col] != 'E'){
        maze -> cells[row][col] = '*';
    }

    //move in any direction and recursively call function
    if(solveMazeDFS(maze, col, row + 1)){
        return 1;
    }
    if(solveMazeDFS(maze, col + 1, row)){
        return 1;
    }
    if(solveMazeDFS(maze, col, row - 1)){
        return 1;
    }
    if(solveMazeDFS(maze, col - 1, row)){
        return 1;
    }

    //backtrack by setting this to a visited path and returning false
    if(maze -> cells[row][col] != 'S' && maze -> cells[row][col] != 'E'){
        maze -> cells[row][col] = '~';
    }

    return 0;
}
