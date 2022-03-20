#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  for(int j = 0; j < 9; j++){
    if(sudoku[i][j] == val){
      return 1;
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO

  for(int i = 0; i < 9; i++){
    if(sudoku[i][j] == val){
      return 1;
    }
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO

  //i is 0-2 range case
  if(i >= 0 && i <= 2){
    //j is 0-2 range case
    if(j >= 0 && j <= 2){
      for(int k = 0; k <= 2; k++){
        for(int l = 0; l <= 2; l++){
          if(sudoku[k][l] == val){
            return 1;
          }
        }
      }
    } 
    //j is 3-5 range case
    if(j >= 3 && j <= 5){
      for(int k = 0; k <= 2; k++){
        for(int l = 3; l <= 5; l++){
          if(sudoku[k][l] == val){
            return 1;
          }
        }
      }
    }
    //j is 6-8 range case
    if(j >= 6 && j <= 8){
      for(int k = 0; k <= 2; k++){
        for(int l = 6; l <= 8; l++){
          if(sudoku[k][l] == val){
            return 1;
          }
        }
      }
    }
  }
  //i is 3-5 range case
  if(i >= 3 && i <= 5){
    //j is 0-2 range case
    if(j >= 0 && j <= 2){
      for(int k = 3; k <= 5; k++){
        for(int l = 0; l <= 2; l++){
          if(sudoku[k][l] == val){
            return 1;
          }
        }
      }
    } 
    //j is 3-5 range case
    if(j >= 3 && j <= 5){
      for(int k = 3; k <= 5; k++){
        for(int l = 3; l <= 5; l++){
          if(sudoku[k][l] == val){
            return 1;
          }
        }
      }
    }
    //j is 6-8 range case
    if(j >= 6 && j <= 8){
      for(int k = 3; k <= 5; k++){
        for(int l = 6; l <= 8; l++){
          if(sudoku[k][l] == val){
            return 1;
          }
        }
      }
    }
  }
  //i is 6-8 range case
  if(i >= 6 && i <= 8){
    //j is 0-2 range case
    if(j >= 0 && j <= 2){
      for(int k = 6; k <= 8; k++){
        for(int l = 0; l <= 2; l++){
          if(sudoku[k][l] == val){
            return 1;
          }
        }
      }
    } 
    //j is 3-5 range case
    if(j >= 3 && j <= 5){
      for(int k = 6; k <= 8; k++){
        for(int l = 3; l <= 5; l++){
          if(sudoku[k][l] == val){
            return 1;
          }
        }
      }
    }
    //j is 6-8 range case
    if(j >= 6 && j <= 8){
      for(int k = 6; k <= 8; k++){
        for(int l = 6; l <= 8; l++){
          if(sudoku[k][l] == val){
            return 1;
          }
        }
      }
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO

  if(is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku)){
    return 0;
  } 

  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int row, col;
  int val = 10;

  //find final empty value in puzzle and store in val
  for(int k = 0; k < 9; k++){
    for(int l = 0; l < 9; l++){
      if(sudoku[k][l] == 0){
        row = k;
        col = l;
        val = sudoku[k][l];
      }
    }
  }
  //if val is still 10 (no empty values in puzzle) we are done so return 1
  if(val == 10){
    return 1;
  }

  for(int input = 1; input <= 9; input++){
    if(is_val_valid(input, row, col, sudoku)){
      sudoku[row][col] = input;
      if(solve_sudoku(sudoku)){
        return 1;
      }
      sudoku[row][col] = 0;
    }
  }

  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





