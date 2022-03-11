/* I implemented all the given functions to the best of my ability. I was able to get countLiveNeighbor to work
 * but I failed to get the other two functions to succesfuly work. I utilized looping through the given
 * 1-D arrays and spent a long time debugging but was unable to figure out what the issue was.
 */

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

    //declare variables to keep track of neighbors, current row, and curren column
    int numLiveNeighbors = 0;
    int curRow = row;
    int curCol = col;

    //loop through adjacent rows
    for(int i = curRow - 1; i <= curRow + 1; i++){
        //check if out of bounds
        if(i >= 0 && i < boardRowSize){
            //loop through adjacent columns
            for(int j = curCol-1; j <= curCol + 1; j++){
                //check if out of bounds
                if(j >= 0 && j < boardColSize){
                    //check if not the point being neighbor checked
                    if(!(row == i && col == j)){
                        //check if this point is a 1
                        if(board[i * boardColSize + j] == 1){
                            //if so, its a neighbor so increment
                            numLiveNeighbors += 1;
                        }
                    } 
                } 
            }
        } 
    }

    return numLiveNeighbors;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {

    //declare variables to check neighbors, current value at cell, length, and a new board
    int numNeighbors = 0;
    int cellVal = 0;
    int len = boardRowSize * boardColSize;
    int boardCopy[len];
    
    //copy elements from board passed in, to board copy
    for(int i = 0; i < len; i++){
        boardCopy[i] = board[i];
    }

    //loop through 1-D array
    for(int row = 0; row < boardRowSize; row++){
        for(int col = 0; col < boardColSize; col++){
            //get num neighbors at selected point of the original copy
            numNeighbors = countLiveNeighbor(boardCopy, boardRowSize, boardColSize, row, col);
            //get cell val at selected point of the original copy
            cellVal = boardCopy[row * boardColSize + col];

            //if the value at the cell is 1 and the number of neighbors is between 2-3, cell is alive
            if(cellVal == 1){
                if(numNeighbors == 2 || numNeighbors == 3){
                    //update board with live cell
                    board[row * boardColSize + col] = 1;
                    continue;
                } else {
                    //else, cell is dead and updated board
                    board[row * boardColSize + col] = 0;
                    continue;
                }
                //if the value at the cell is 0 and the number of neighbors is 3, cell is alive
            } else if (cellVal == 0){
                if(numNeighbors == 3){
                    //update board with live cell
                    board[row * boardColSize + col] = 1;
                    continue;
                } 
            }
            
        }
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){

    //declre variables, boolean to check if its same, length, and a copy of the board
    int isSame = 0;
    int len = boardRowSize * boardColSize;
    int prevBoard[len];

    //copy board into prevboard variable to keep a copy
    for(int i = 0; i < len; i++){
        prevBoard[i] = board[i];
    }

    //call updateBoard on original
    updateBoard(board, boardRowSize, boardColSize);

    //create new board to store updated original board after updateBoard was called
    int newBoard[len];
    for(int i = 0; i < len; i++){
        newBoard[i] = board[i];
    }

    //compare the two boards, if the elements are the same, keep is same as 1
    for(int i = 0; i < len; i++){
        if(prevBoard[i] == newBoard[i]){
            isSame = 1;
        } else {
            //the minute they aren't the same, just return 0
            return 0;
        }
    }
    //by the end of it, return isSame
    return isSame;
}

				
				
			

