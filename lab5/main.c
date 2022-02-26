#include <stdio.h>
#include <stdlib.h> 
#include <dice.h>

/* Code to simulate rolling three six-sided dice (D6)
 * User first types in seed value
 * Use seed value as argument to srand()
 * Call roll_three to generate three integers, 1-6
 * Print result "%d %d %d "
 * If triple, print "Triple!\n"
 * If it is not a triple but it is a dobule, print "Double!\n"
 * Otherwise print "\n"
 */

int main() {
    
    //seed var
    int seedVal;

    //roll_three vars
    int firstVal;
    int secondVal;
    int thirdVal;

    //I/O
    printf("Enter Seed: ");
    scanf("%d", &seedVal);
    
    //set up RNG and generate values
    srand(seedVal);
    roll_three(&firstVal, &secondVal, &thirdVal);

    //print output
    if(firstVal == secondVal && secondVal == thirdVal){
        printf("%d %d %d Triple!", &firstVal, &secondVal, &thirdVal);
    } else if (firstVal == secondVal || firstVal == thirdVal || secondVal == thirdVal){
        printf("%d %d %d Double!", &firstVal, &secondVal, &thirdVal);
    } else {
        printf("%d %d %d", &firstVal, &secondVal, &thirdVal);
    }


}

