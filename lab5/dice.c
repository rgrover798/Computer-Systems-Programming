#include <stdio.h>
#include <stdlib.h> 
//Function for generating three d6 rolls

void roll_three(int* one, int* two, int* three){
    *one = rand() % 6 + 1;
    *two = rand() % 6 + 1;
    *three = rand() % 6 + 1;
}
