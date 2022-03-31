/*
 * I found this MP extremely intuitive as a lot of the code had to be written from scratch, as well as it allowed
 * me to improve my knowledge of pointers and structs. For the first function make_game, I used the -> to assign
 * the variables to their attritbutes defined in the struct, as well as looped through the game object to set
 * each cell of the grids to -1 or empty. For remake_game, I modified the attributes the same way with the new
 * row and column attributes passed into the function. Looped like previous function as well to set all values to
 * -1. For get_cell, I checked the bounds 0 to number of columns/rows which I got from the game object attributes 
 * in order to check if the selected cell was in the bounds of the gameboard. For the move w,a,s,d, I used the 
 * algorithm from lab 8 which was slightly modified to account for differences in direction, as well as combining
 * adjacent tiles if their values were the same. Finally for the last function legal_move, I loop through each cell
 * first checking if it is empty, then checking the neighbor above and next to it to see if there are any adjacent
 * values that are equal. If these values are equal then the game is not done but if there are no adjacaent
 * equal values or empty cells, game is over. Overall, I found the MP very enjoyable since it tested a lot of
 * concepts that we have learned over the last few weeks which was good preperation for the next midterm. 
 *
 */

#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    //set variables and set score to 0
    mygame->rows = rows;
    mygame->cols = cols;
    mygame->score = 0;
    //loop through game board to fill cell values with -1
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mygame->cells[i * cols + j] = -1;
        }
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
     //update board with new_rows and new_cols
     (*_cur_game_ptr)->rows = new_rows;
     (*_cur_game_ptr)->cols = new_cols;
     (*_cur_game_ptr)->score = 0;

    //loop through game board and set all values to -1.
     for(int i = 0; i < new_rows; i++){
        for(int j = 0; j < new_cols; j++){
            (*_cur_game_ptr)->cells[i * new_cols + j] = -1;
        }
    }

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    //check bounds if row is between the number or rows and 0 and same with column
    if(row > cur_game -> rows || row < 0 || col > cur_game-> cols || col < 0){
        return NULL;
    } else {
        //return pointer
        return &cur_game->cells[row * cur_game->cols + col];
    }
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int numRows = cur_game -> rows;
    int numCols = cur_game -> cols;
    int curScore = cur_game -> score;
    //create copy of board filled with all -1 to keep track of changes made to board
    int sampleSpace[numRows][numCols];
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            sampleSpace[i][j] = -1;
        }
    }
    //declare and initialize return value which is 0 by default
    int retVal = 0;
    //lab 8 algorithim
    //loop through rows from start
    for(int curRow = 0; curRow < numRows; curRow++){
        //loop through columns from start
        for(int curCol = 0; curCol < numCols; curCol++){
            //find first non empty cell
            if(!(cur_game -> cells[curRow * numCols + curCol] == -1)){
                //loop till curRow so you find minimum row 
                for(int swapRow = 0; swapRow <= curRow; swapRow++){
                    //declare variable complete to check if the swap is done and ready to merge
                    int complete = 0;
                    //find empty cell at current value in current column
                    if(cur_game->cells[swapRow*numCols + curCol] == -1){
                        //swap values at row indexes
                        cur_game -> cells[swapRow * numCols + curCol] = cur_game -> cells[curRow * numCols + curCol];
                        cur_game -> cells[curRow * numCols + curCol] = -1;
                        //set returnVal to 1 since move is valid and complete to 1 since move is complete and ready to merge
                        complete = 1;
                        retVal = 1;
                    } 
                    //accounting for combining values
                    if(curRow == swapRow || complete == 1){
                        //calculate values at current row and row above
                        int swapRowVal = cur_game -> cells[swapRow * numCols + curCol];
                        int swapRowPrevVal = cur_game -> cells[(swapRow - 1) * numCols + curCol];
                        //check if both values are equal, and if it isnt the first row, and if it hasn't already been merged which is tracked by the copy of board
                        if(sampleSpace[swapRow-1][curCol] == -1 && swapRow != 0 && swapRowVal == swapRowPrevVal){
                            //combine values, update score, store change in copy of board so it is not repeated
                            cur_game -> cells[(swapRow - 1) * numCols + curCol] = swapRowVal + swapRowPrevVal;
                            cur_game -> cells[swapRow * numCols + curCol] = -1;
                            cur_game -> score = curScore + (swapRowVal + swapRowPrevVal);
                            sampleSpace[swapRow - 1][curCol] = 0;
                            retVal = 1;
                        }
                        //it is complete, so break loop and jump to next value
                        break;
                    }
                }
            }
        }
    }

    return retVal;
};

//see comments for move_w which are similiar to move_s as to how it works
int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int numRows = cur_game -> rows;
    int numCols = cur_game -> cols;
    int curScore = cur_game -> score;
    int sampleSpace[numRows][numCols];
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            sampleSpace[i][j] = -1;
        }
    }
    int retVal = 0;
    
    //alter algorithm slightly to account for different direction
    //loop from last row to first since going down
    for(int curRow = numRows - 1; curRow >= 0; curRow--){
        //loop from first column to last
        for(int curCol = 0; curCol < numCols; curCol++){
            if(!(cur_game -> cells[curRow * numCols + curCol] == -1)){
                //loop from last row till whatever curRow is to find closest row
                for(int swapRow = numRows - 1; swapRow >= curRow; swapRow--){
                    int complete = 0;
                    if(cur_game->cells[swapRow*numCols + curCol] == -1){
                        //swap values at row indexes
                        cur_game -> cells[swapRow * numCols + curCol] = cur_game -> cells[curRow * numCols + curCol];
                        cur_game -> cells[curRow * numCols + curCol] = -1;
                        //set returnVal to 1 since move is valid and complete to 1 since move is complete
                        retVal = 1;
                        complete = 1;
                    } 
                    if(curRow == swapRow || complete == 1){
                        //calculate values at current row and row above
                        int swapRowVal = cur_game -> cells[swapRow * numCols + curCol];
                        int swapRowPrevVal = cur_game -> cells[(swapRow + 1) * numCols + curCol];
                        if(sampleSpace[swapRow + 1][curCol] == -1 && swapRow != 0 && swapRowVal == swapRowPrevVal){
                            retVal = 1;
                            //combine values, update score, store change in copy of board so it is not repeated
                            cur_game -> cells[(swapRow + 1) * numCols + curCol] = swapRowVal + swapRowPrevVal;
                            cur_game -> cells[swapRow * numCols + curCol] = -1;
                            cur_game -> score = curScore + (swapRowVal + swapRowPrevVal);
                            sampleSpace[swapRow + 1][curCol] = 0;
                        }
                        break;
                    }
                }
            }
        }
    }



    return retVal;
};

//see comments for move_w which are slightly similiar to move_a as to how it works
int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int numRows = cur_game -> rows;
    int numCols = cur_game -> cols;
    int curScore = cur_game -> score;
    int sampleSpace[numRows][numCols];
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            sampleSpace[i][j] = -1;
        }
    }
    int retVal = 0;

    //alter algorithm slightly to account for different direction
    //loop from first to last row
    for(int curRow = 0; curRow < numRows; curRow++){
        //loop from first to last column
        for(int curCol = 0; curCol < numCols; curCol++){
            if(!(cur_game -> cells[curRow * numCols + curCol] == -1)){
                //loop from first col to curCol to find next available column
                for(int swapCol = 0; swapCol <= curCol; swapCol++){
                    int complete = 0;
                    if(cur_game->cells[curRow*numCols + swapCol] == -1){
                        //swap values at column indexes
                        cur_game -> cells[curRow * numCols + swapCol] = cur_game -> cells[curRow * numCols + curCol];
                        cur_game -> cells[curRow * numCols + curCol] = -1;
                        //set returnVal to 1 since move is valid and complete to 1 since move is complete
                        retVal = 1;
                        complete = 1;
                    } 
                    if(curCol == swapCol || complete == 1){
                        //calculate values at current column and column adjacent
                        int swapRowVal = cur_game -> cells[curRow * numCols + swapCol];
                        int swapRowPrevVal = cur_game -> cells[curRow * numCols + swapCol - 1];
                        if(sampleSpace[curRow][swapCol - 1] == -1 && swapCol != 0 && swapRowVal == swapRowPrevVal){
                            retVal = 1;
                            //combine values, update score, store change in copy of board so it is not repeated
                            cur_game -> cells[curRow * numCols + swapCol - 1] = swapRowVal + swapRowPrevVal;
                            cur_game -> cells[curRow * numCols + swapCol] = -1;
                            cur_game -> score = curScore + (swapRowVal + swapRowPrevVal);
                            sampleSpace[swapCol - 1][curCol] = 0;
                        }
                        break;
                    }
                }
            }
        }
    }



    return retVal;
};

//see comments for move_w which are slightly similiar to move_d as to how it works
int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int numRows = cur_game -> rows;
    int numCols = cur_game -> cols;
    int curScore = cur_game -> score;
    int sampleSpace[numRows][numCols];
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            sampleSpace[i][j] = -1;
        }
    }
    int retVal = 0;

    //alter algorithm slightly to account for different direction
    //loop from first to last row
    for(int curRow = 0; curRow <= numRows; curRow++){
        //loop from last to first column
        for(int curCol = numCols - 1; curCol >= 0; curCol--){
            if(!(cur_game -> cells[curRow * numCols + curCol] == -1)){
                //loop from last column to closest curCol to find closest -1 value
                for(int swapCol = numCols - 1; swapCol >= curCol; swapCol--){
                    int complete = 0;
                    if(cur_game->cells[curRow * numCols + swapCol] == -1){
                        //swap values at column indexes
                        cur_game -> cells[curRow * numCols + swapCol] = cur_game -> cells[curRow * numCols + curCol];
                        cur_game -> cells[curRow * numCols + curCol] = -1;
                        //set returnVal to 1 since move is valid and complete to 1 since move is complete
                        retVal = 1;
                        complete = 1;
                    } 
                    if(curCol == swapCol || complete == 1){
                        //calculate values at current column and column adjacent
                        int swapRowVal = cur_game -> cells[curRow * numCols + swapCol];
                        int swapRowPrevVal = cur_game -> cells[curRow * numCols + swapCol + 1];
                        if(sampleSpace[curRow][swapCol + 1] == -1 && curRow != 0 && swapRowVal == swapRowPrevVal){
                            retVal = 1;
                            //combine values, update score, store change in copy of board so it is not repeated
                            cur_game -> cells[curRow * numCols + swapCol + 1] = swapRowVal + swapRowPrevVal;
                            cur_game -> cells[curRow * numCols + swapCol] = -1;
                            cur_game -> score = curScore + (swapRowVal + swapRowPrevVal);
                            sampleSpace[curRow][swapCol + 1] = 0;
                        }
                        break;
                    }
                }
            }
        }
    }

    return retVal;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int numRows = cur_game -> rows;
    int numCols = cur_game -> cols;
    int retVal = 0; 
    int adjCell = 0;
    int val = 0;

    //loop through game board
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            //get value at cell
            val = cur_game -> cells[i * numCols + j];
            //if cell empty, return 1
            if(val == -1){
                retVal = 1;
            } 
            //get value at cell on right
            adjCell = cur_game -> cells[i * numCols + j + 1];
            //if value on right equals value at selected cell, return 1
            if(adjCell == val && (j + 1) < numCols){
                retVal = 1;
                continue;
            }
            //get value at cell on top
            adjCell = cur_game -> cells[(i + 1) * numCols + j];
            //if value on top equals value at selected cell, return 1
            if(adjCell == val && (i + 1) < numRows){
                retVal = 1;
                continue;
            }
        }
    }
    return retVal;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
