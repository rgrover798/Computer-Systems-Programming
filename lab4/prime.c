#include "prime.h"

int is_prime(int n){
  int isPrime = 0;

  if(n == 2){
    return 1;
  }

  for(int i = 2; i < n; i++){
    if(n % i == 0){
      return 0;
    } else {
      isPrime = 1;
    }
  }

  return isPrime;
}
