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

    int numLiveNeighbors = 0;
    int curRow = row;
    int curCol = col;

    for(int i = curRow - 1; i <= curRow + 1; i++){
        if(i > 0 && i < boardRowSize){
            for(int j = curCol-1; j <= curRow + 1; j++){
                if(j > 0 && j < boardColSize){
                    if(row != curRow && col != curCol){
                        if(board[i * boardColSize + j] == 1){
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

    int numNeighbors = 0;
    int cellVal = 0;

    for(int i = 0; i < boardRowSize; i++){
        for(int j = 0; j < boardColSize; j++){
            numNeighbors = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);
            cellVal = board[i * boardColSize + j];
            if(cellVal == 1 && numNeighbors < 2){
                board[i * boardColSize + j] = 0;
            } else if (cellVal == 1 && (numNeighbors == 2 || numNeighbors == 3)){
                board[i * boardColSize + j] = 1;
            } else if (cellVal == 1 && numNeighbors > 3){
                board[i * boardColSize + j] = 0;
            } else if (cellVal == 0 && numNeighbors == 3){
                board[i * boardColSize + j] = 1;
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

    int isSame = 0;
    int len = boardRowSize * boardColSize;
    int prevBoard[len];
    for(int i = 0; i < len; i++){
        prevBoard[i] = board[i];
    }

    updateBoard(* board, boardRowSize, boardColSize);

    int newBoard[len];
    for(int i = 0; i < len; i++){
        newBoard[i] = board[i];
    }

    for(int i = 0; i < len; i++){
        if(prevBoard[i] == newBoard[i]){
            isSame = 1;
        } else {
            return 0;
        }
    }
    return isSame;
}

				
				
			

