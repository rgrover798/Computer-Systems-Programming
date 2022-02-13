#include <stdio.h>
#include <stdlib.h>

/*
 * main
 *  DESCRIPTION: Print a selected row of pascal's triangle given the row
 *  INPUTS: console (int) - row requested to print
 *  OUTPUTS: console (k_term) -- each coefficient of the row requested
 *  RETURN VALUE: 0
 *  SIDE EFFECTS: none
 */
int main()
{
  // Declare and initialize variables
  int row = 0;
  unsigned int k_term = 1;

  // get user input
  printf("Enter a row index: ");
  scanf("%d", &row);

  //print default case
  printf("1 ");

  /*begin looping process, calculate k_term using equation provided and looping
  through each value in row selected except the first*/
  for(int i = 1; i <= row; i++){
    for(int j = 1; j <= i; j++){
        k_term = k_term * (row + 1 - j)/j;
    }
    //print each k_term and reset value
    printf("%d ", k_term);
    k_term = 1;
  }
  return 0;
}
