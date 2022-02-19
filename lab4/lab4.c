#include <stdio.h>
#include "prime.h"

int main(){
  int input;

  printf("Enter the value of n: ");
  scanf("%d", &input);
  printf("Printing primes less than or equal to %d:\n", input);

  for(int i = 1; i <= input; i++){
    if(is_prime(i) == 1){
      printf("%d ", i);
    } 
  }
printf("\n");
  return 0;
}

