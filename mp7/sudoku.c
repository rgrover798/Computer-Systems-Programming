#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

/* INTRO PARAGRAPH
/  In MP7, I completed the functions is_val_in_row, is_val_in_col, is_val_in_3x3_zone, is_val_valid, and solve_sudoku.
/  The approach I took for is_val_in_row and is_val_in_col was very similiar by looping through the given row or column
/  until I found the value being searched for in that row or column and returning true (1) or false (0) depending upon if
/  the value was found in that row or column. For is_val_in_3x3_zone, I used nested if/else statements to first determine
/  the zone I was in, and then loop through that zone using nested loops until I found the val being searched for in that zone
/  If that val isn't found, then I know it doesn't exist in that 3x3 zone so I returned false (0) and if it does exist which
/  I determine through the nested for loops, then I return true (1). For the is_val_valid, I used the previous 3 functions
/  I just explained with an if statement. If any of those functions return true, then I wouldn't be able to put a given value
/  in that spot, so I used that logic in the if statement to determine is the value was valid at that point. For the solve_sudoku
/  function, I used a recursive approach by first checking if the puzzle was solved already, and if not, finding an empty
/  cell to then fill in using the function is_val_valid for each value in the range of 1-9 inclusive since those are
/  the standard sudoku values.
*/

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  //set up loop to loop through every value in the given row
  for(int j = 0; j < 9; j++){
    //if the row has a value that matches that of the input val, then return true (1)
    if(sudoku[i][j] == val){
      return 1;
    }
  }

  //if there are no values that match the given val in this row, return false (0)
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO

  //set up loop to loop through every value in the given column
  for(int i = 0; i < 9; i++){
    //if the column has a value that matches that of the input val, then return true (1)
    if(sudoku[i][j] == val){
      return 1;
    }
  }
  
  //if there are no values that match the given val in this column, return false (0)
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO

  /* first set up if statements to determine which 3x3 zone we are checking. Then set up corresponding loops 
  /  to go through each of these zones determined by the if statements. If there is a value in this zone that
  /  matches that of the input "val", then we know that there is already a value in that 3x3 zone that exists
  /  so we can return true (1). Else by default, we will return false (0), if the value does not exist in the
  /  selected 3x3 zone. The code below could have been shortened with switch statements but I decided to use
  /  nested if/else statements. Below I labeled each case so it is easier to follow. A lot of the code is duplicated
  /  with minor values changed on the loops depending on the for loop of the selected 3x3 zone.
  */
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

  /* If the value already exists in a row, column, or 3x3 zone given by i and j, then we return 0 since that value
  /  would be invalid in that location. 
  */
  if(is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku)){
    return 0;
  } 

  // else by default, we just return 1 since it would be valid if not invalid by the tests above.
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  
  //declare row and column variables to keep track of which 0 value is being changed, as well a test variable val
  int row, col;
  int val = 10;

  //find the final empty value in the puzzle at the given recursive spot and store in val
  for(int k = 0; k < 9; k++){
    for(int l = 0; l < 9; l++){
      if(sudoku[k][l] == 0){
        //set row, col to k, l which correspond to i and j in the functions above.
        row = k;
        col = l;
        //if there is a 0 value, set val to that 0 values at sudoku[k][l]
        val = sudoku[k][l];
      }
    }
  }
  //if val is still 10 and no 0 values were found above in the loops, return true (1) meaning the puzzle is solved
  if(val == 10){
    return 1;
  }

  //loop through possible input values for sudoku puzzle which is from 1-9 inclusive
  for(int input = 1; input <= 9; input++){
    //if the current input value on the loop is valid, set the corresponding row and col to that input value
    if(is_val_valid(input, row, col, sudoku)){
      sudoku[row][col] = input;
      //recursively call solve_sudoku again to solve updated puzzle with new value, if the puzzle is complete, return true (1)
      if(solve_sudoku(sudoku)){
        return 1;
      }
      // else, set that row/col to 0 and continue to loop through possible input values from 1-9 inclusive till one of them is valid
      sudoku[row][col] = 0;
    }
  }

  //return 0 by default
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





