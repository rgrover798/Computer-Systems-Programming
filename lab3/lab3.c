#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/*
 * main
 *  DESCRIPTION: compute a set of points of a function and print the results
 *  INPUTS: console (int, float float) -- equation related constants
 *  OUTPUTS: console (x, f(x)) -- sequence of values to be printed
 *  RETURN VALUE: 0
 *  SIDE EFFECTS: none
 */
int main()
{
    // Declare variables
    int num;
    float firstW;
    float secondW;

    // Prompt user for input
    printf("Enter the values of n, omega1, and omega2 in that order \n");
    
    // Get user input
    scanf("%d%f%f", &num, &firstW, &secondW);
    
    // Compute function output
    /* for i from 0 to n-1
     *     compute and print xi and f(xi)
     *     use sin() function from math.h
     */
    if(num < 1){
        printf("Invalid input");
        return 0;
    }

    for(int i = 0; i < num; i++){
        float xi = (i * M_PI)/num;
        float out = sin(firstW * xi) + 0.5 * sin(secondW * xi);
        printf("(%f, %f)\n", xi, out);
    }
    return 0;
}