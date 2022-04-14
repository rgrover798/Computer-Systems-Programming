#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>




//DONE
sp_tuples * load_tuples(char* input_file)
{
    //initialize variables
    int rows, cols;
    int rowIndex, colIndex;
    double val;
    
    //start file
    FILE * myfile = fopen(input_file, "r");

    //set rows and cols of tuple, set nz to 0 and tuples_head to NULL
    fscanf(myfile, "%d %d", &rows, &cols);
    sp_tuples * myTuple = malloc(sizeof(sp_tuples));
    myTuple -> m = rows;
    myTuple -> n = cols;
    myTuple -> nz = 0;
    myTuple -> tuples_head = NULL;

    //loop through file to EOF is reached
    while(fscanf(myfile, "%d %d %lf", &rowIndex, &colIndex, &val) != EOF){
        //set each input as a node to the tuple
        set_tuples(myTuple, rowIndex, colIndex, val);  
    } 

    //close file
    fclose(myfile);
    return myTuple;
}


//DONE
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    //save currentNode as head
    sp_tuples_node * currentNode = mat_t -> tuples_head;
    //loop through linked list till NULL
    while(currentNode != NULL){
        //if row and col match on the currentnode, return value at this node
        if(currentNode -> row == row && currentNode -> col == col){
            return currentNode -> value;
        //else, increment to next node
        } else {
            currentNode = currentNode -> next;
        }
    }
    return 0;
}


//DONE
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    //keeps track of current node as well has previous and next
    sp_tuples_node * currentNode = mat_t -> tuples_head;
    sp_tuples_node * prevNode = NULL, * nextNode = NULL;

    //case if input value is 0
    if(value == 0 && gv_tuples(mat_t, row, col) != 0){
        //check if matrix is empty
        while(currentNode != NULL){
            nextNode = currentNode -> next;
            //check if row and column match
            if(currentNode -> row == row && currentNode -> col == col){
                //check if matrix only has one entry, if so, free that one entry and set end to NULL and decrement
                if(prevNode == NULL){
                    mat_t -> tuples_head = nextNode;
                    free(currentNode);
                    currentNode = NULL;
                    mat_t -> nz -= 1;
                    break;
                //else, free node and rearrange pointers, set free'd node to NULL and decrement
                } else {
                    prevNode -> next = nextNode;
                    free(currentNode);
                    currentNode = NULL;
                    mat_t -> nz -= 1;
                    break;
                }
            }
            //replace prevNode with currentNode to update what the previous node is
            prevNode = currentNode;
            //go to next node
            currentNode = currentNode -> next;
        }
    }

    //case if input value is non-zero and node exists 
    if(value != 0 && gv_tuples(mat_t, row, col) != 0){
        currentNode = mat_t -> tuples_head;
        //loop till end of linked-list is reached
        while(currentNode != NULL){
            //check if row and col match
            if(currentNode -> row == row && currentNode -> col == col){
                //update value and break
                currentNode -> value = value;
                break;
            } else {
                //increment to next node
                currentNode = currentNode -> next;
            }
        } 
    }
    
    //case if input value is non-zero and node does NOT exist
    if(value != 0 && gv_tuples(mat_t, row, col) == 0){
        //case if matrix is non empty
        currentNode = mat_t -> tuples_head;
        prevNode = NULL;
        //check if currentNode is not NULL (not empty matrix)
        while(currentNode != NULL){
            //get current index and index you want to swap
            int curNodeIndex = currentNode -> row * mat_t -> m + currentNode -> col;
            int swapNodeIndex = row * mat_t -> m + col;
            //compare indices and check if prevNode is NULL (beginning of matrix)
            if(prevNode == NULL && curNodeIndex > swapNodeIndex){
                //if so, create new header node and rearrange pointers, and increment, then break
                sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
                newNode -> row = row;
                newNode -> col = col;
                newNode -> value = value;
                mat_t -> tuples_head = newNode;
                newNode -> next = currentNode; 
                mat_t -> nz += 1;
                break;
            } 
            //if it isn't the beginning of matrix and the swapNode index is smaller
            //place new node right behind current node and rearrange pointers. Increment and then break
            if(prevNode != NULL && curNodeIndex > swapNodeIndex){
                sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
                newNode -> row = row;
                newNode -> col = col;
                newNode -> value = value;
                newNode -> next = currentNode;
                prevNode -> next = newNode;
                mat_t -> nz += 1;
                break;
            } 

            //if it is the end of the matrix, add the new node to the end of the matrix
            //rearrange pointers and increment non zeros
            if(currentNode -> next == NULL){
                sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
                newNode -> row = row;
                newNode -> col = col;
                newNode -> value = value;
                currentNode -> next = newNode;
                newNode -> next = NULL;
                mat_t -> nz += 1;
                break;
            }
            //unconditionally set previous node to be the current node and jump to next node in list
            prevNode = currentNode;
            currentNode = currentNode -> next;
        }
        //case if matrix is empty
        if(mat_t -> tuples_head == NULL){
            //create new tuple_head node and increment nz
            sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
            newNode -> row = row;
            newNode -> col = col;
            newNode -> value = value;
            newNode -> next = NULL;
            mat_t -> tuples_head = newNode;
            mat_t -> nz += 1;
        }
    }
    
}


//DONE
void save_tuples(char * file_name, sp_tuples * mat_t)
{
    //start by checking if null matrix, then no output file
    if(mat_t != NULL){
        //associate rows and cols of mat_t with variables and declare value variable
        int rows = mat_t -> m;
        int cols = mat_t -> n;
        double value;
        
        //open output file for writing and write the rows and cols and increment to new line after
        FILE * outFile = fopen(file_name, "w");
        fprintf(outFile, "%d %d\n", rows, cols);

        //set current node to head of linked list and loop through list till NULL
        sp_tuples_node * currentNode = mat_t -> tuples_head;
        while(currentNode != NULL){
            //set rows, cols, and value, equal to associated current node
            rows = currentNode -> row;
            cols = currentNode -> col;
            value = currentNode -> value;
            //print in order and go to new line
            fprintf(outFile, "%d %d %f\n", rows, cols, value);
            //set current node to next node
            currentNode = currentNode -> next;
        }
        //close write file
        fclose(outFile);
    }
}


//DONE
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
    //create new matrix C to store summation
    sp_tuples * matC = NULL;
    //check if matrices are valid, if so, begin construction of matC based on A and B
    if(matA -> m == matB -> m && matA -> n == matB -> n && matA != NULL && matB != NULL){
        matC = malloc(sizeof(sp_tuples));
        matC -> m = matA -> m;
        matC -> n = matA -> n;
        matC -> nz = 0;
        matC -> tuples_head = NULL;

        //use currentNodeA to store current location in linked list A
        sp_tuples_node * currentNodeA = matA -> tuples_head;
        //use currentNodeB to store current location in linked list B
        sp_tuples_node * currentNodeB = matB -> tuples_head;
        //use currentNode to track progress through linked list C
        sp_tuples_node * currentNode = NULL;

        //add every value of linked list A to linked list C using set_tuples
        while(currentNodeA != NULL){
            set_tuples(matC, currentNodeA -> row, currentNodeA -> col, currentNodeA -> value);
            currentNodeA = currentNodeA -> next;
        }

        //do the same for linked list B. If a value already exists add it to the corresponding coordinates in C
        double sum;
        while(currentNodeB != NULL){
            //if node already doesn't exist, just add the node to linked list
            if(gv_tuples(matC, currentNodeB -> row, currentNodeB -> col) == 0){
                set_tuples(matC, currentNodeB -> row, currentNodeB -> col, currentNodeB -> value);
            //case for if node already exists
            } else {
                currentNode = matC -> tuples_head;
                //loop through list till end is reached
                while(currentNode != NULL){
                    //if row and col match, get sum and set corresponding row and col in C to this sum then break
                    if(currentNodeB -> row == currentNode -> row && currentNodeB -> col == currentNode -> col){
                        sum = currentNode -> value + currentNodeB -> value;
                        set_tuples(matC, currentNodeB -> row, currentNodeB -> col, sum);
                        break;
                    }
                    //if it doesn't match, go to next node
                    currentNode = currentNode -> next;
                }
            }
            //unconditonally go to next node for B to add it to C
            currentNodeB = currentNodeB -> next;
        }
    } 
    //if matC is not NULL, return it
    if(matC != NULL){
        return matC;
    }
	return NULL;
}


//if i have time tomorrow
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{ 
    
    return NULL; 
}

//DONE
//free accordingly, each node, then matrix overall
void destroy_tuples(sp_tuples * mat_t)
{
	sp_tuples_node * currentNode = mat_t -> tuples_head;
    sp_tuples_node * temp = NULL;
    //loop through linked list till NULL pointer is reached
    while(currentNode != NULL){
        //set temp node to next node in linked list
        temp = currentNode -> next;
        free(currentNode);
        //set current node to temp (the next node in the list)
        currentNode = temp;
    }
    currentNode = NULL;
    free(mat_t);
    mat_t = NULL;
}  

/*
 * ----------------------------------------------------------------------------
 * BELOW ARE FUNCTIONS THAT I USED TO USE BUT THE CODE DIDN'T WORK SO I REWROTE
 * ----------------------------------------------------------------------------
 */
// 1st Old Function: OLD function for set_tuples
// if(value == 0){
//         while(currentNode != NULL){
//             nextNode = currentNode -> next;
//             if(currentNode -> row == row && currentNode -> col == col){
//                 if(prevNode == NULL){
//                     mat_t -> tuples_head = nextNode;
//                     free(currentNode);
//                     currentNode = NULL;
//                     break;
//                 } else {
//                     prevNode -> next = nextNode;
//                     free(currentNode);
//                     currentNode = NULL;
//                     break;
//                 }
//             } else {
//                 prevNode = currentNode;
//                 currentNode = currentNode -> next;
//             }
//         }
//         mat_t -> nz -= 1;
//     } 

//     currentNode = mat_t -> tuples_head;
//     while(currentNode != NULL){
//         if(currentNode -> row == row && currentNode -> col == col){
//             currentNode -> value = value;
//             break;
//         } else {
//             currentNode = currentNode -> next;
//         }
//     } 
//     currentNode = mat_t -> tuples_head;
//     prevNode = NULL;
//     while(currentNode != NULL){
//         int curNodeIndex = currentNode -> row * mat_t -> m + currentNode -> col;
//         int swapNodeIndex = row * mat_t -> m + col;
//         if(prevNode == NULL && curNodeIndex > swapNodeIndex){
//             sp_tuples_node * newHead = malloc(sizeof(sp_tuples_node));
//             newHead -> row = row;
//             newHead -> col = col;
//             newHead -> value = value;
//             mat_t -> tuples_head = newHead;
//             newHead -> next = currentNode; 
//             mat_t -> nz += 1;
//             break;
//         } else {
//             if(curNodeIndex > swapNodeIndex){
//                 sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
//                 newNode -> row = row;
//                 newNode -> col = col;
//                 newNode -> value = value;
//                 newNode -> next = currentNode;
//                 prevNode -> next = newNode;
//                 mat_t -> nz += 1;
//                 break;
//             }
//         }
//         prevNode = currentNode;
//         currentNode = currentNode -> next;
//     }


//2nd Old Function: Old function for sorting algorithm
// //currentNode keeps track of the current node that is being looked at in that moment of time
//     sp_tuples_node * currentNode = myTuple -> tuples_head;
//     //swapNode keeps track of the node to be swapped in that moment of time
//     sp_tuples_node * swapNode = NULL;
//     //testNode keeps track of the overall node from the head, to tail that is being checked for being in order
//     sp_tuples_node * testedNode = myTuple -> tuples_head;

//     //set up loop to overall loop through the whole tuple
//     for(int i = 0; i < myTuple -> nz; i++){
//         //if it isnt the first iteration, then increment the testedNode to the nextNode and set currentNode to that
//         if(i != 0){
//             testedNode = testedNode -> next;
//             currentNode = testedNode;
//         }
//         //set swapNode which will go through the whole linked list to the beginning of the linked list
//         swapNode = myTuple -> tuples_head;
//         //loop through the linked list till NULL
//         while(currentNode != NULL){
//             //get the index of the current node (whatever node is being checked for, if 0th iteration then head node)
//             int curNodeIndex = currentNode -> row * myTuple -> m + currentNode -> col;
//             //get the index of the swap node, which is the head node on the 0th iteration
//             int swapNodeIndex = swapNode -> row * myTuple -> m + swapNode -> col;
//             //if the current node index > the index of the current node being checked, swap the values of those two nodes
//             if(curNodeIndex > swapNodeIndex){
//                 int tempRow = currentNode -> row;
//                 int tempCol = currentNode -> col;
//                 double tempVal = currentNode -> value;

//                 currentNode -> row = swapNode -> row;
//                 currentNode -> col = swapNode -> col;
//                 currentNode -> value = swapNode -> value;

//                 swapNode -> row = tempRow;
//                 swapNode -> col = tempCol;
//                 swapNode -> value = tempVal;
//             //else, increment to the next possible node in the linked list
//             } else {
//                 swapNode = swapNode -> next;
//             }
//         }
//     }
//     return myTuple;

// 3rd Old Function: Old function for adding two matrices
// int curRowA, curColA, curRowB, curColB, i, j, sum;
//         for(i = 0; i < matA -> nz; i++){
//             currentNodeB = matB -> tuples_head;
//             for(j = 0; j < matB -> nz; j++){
//                 curRowA = currentNodeA -> row;
//                 curColA = currentNodeA -> col;
//                 curRowB = currentNodeB -> row;
//                 curColB = currentNodeB -> col;

//                 if(curRowA == curRowB && curColA == curColB){
//                     sum = currentNodeA -> value + currentNodeB -> value;
//                     if(sum != 0){
//                         if(matC -> nz == 0){
//                             sp_tuples_node * headNode = malloc(sizeof(sp_tuples_node));
//                             headNode -> row = curRowA;
//                             headNode -> col = curColA;
//                             headNode -> value = sum;

//                             matC -> tuples_head = headNode;
//                             headNode -> next = NULL;
//                             prevNode = headNode;

//                             matC -> nz += 1;
//                         } else {
//                             sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
//                             newNode -> row = curRowA;
//                             newNode -> col = curColA;
//                             newNode -> value = sum;

//                             prevNode -> next = newNode;
//                             newNode -> next = NULL;
//                             prevNode = newNode;

//                             matC -> nz += 1;
//                         }
//                     }
//                 }
//                 currentNodeB = currentNodeB -> next;
//             }
//             currentNodeA = currentNodeA -> next;
//         }

//4th old function: Old function for getting input from file
//sp_tuples_node * headNode = NULL;
//sp_tuples_node * nextNode = NULL;
// if(val != 0){
        //     //allocate memory for the nextnode and set values of nextNode
        //     nextNode = malloc(sizeof(sp_tuples_node));
        //     nextNode -> row = rowIndex;
        //     nextNode -> col = colIndex;
        //     nextNode -> value = val;
        //     //point to headNode (aka NULL for the first term) since it is put at the end of the linked list
        //     nextNode -> next = headNode;
        //     myTuple -> nz += 1;
        //     //set headNode equal to the nextNode to save pointer to the nextNode
        //     headNode = nextNode;
        // }
//myTuple -> tuples_head = headNode;

//5th Old Function: Old function for sorting nodes
/*
     * -----------
     * ORDER NODES
     * -----------
     */

    //variables (some are temporary) for swapping in insertion sort as well as looping
    // int tempRow, tempCol, testNodeIndex, swapNodeIndex, i, j;
    // double tempVal;
    // sp_tuples_node * currentNode = myTuple -> tuples_head;
    // sp_tuples_node * testNode, * swapNode;

    // //insertion sort through linked list to sort values
    //  for(i = 0; i < myTuple -> nz; i++){
    //      if(i != 0){
    //          currentNode = currentNode -> next;
    //      }
    //      testNode = currentNode;
    //      swapNode = currentNode;
    //      for(j = 0; j < myTuple -> nz; j++){
    //          testNodeIndex = testNode -> row * myTuple -> m + testNode -> col;
    //          swapNodeIndex = swapNode -> row * myTuple -> m + swapNode -> col;
    //          if(testNodeIndex < swapNodeIndex){
    //              swapNode = testNode;
    //          }
    //          testNode = testNode -> next;
    //          if(testNode == NULL){
    //              break;
    //          }
    //      }

    //      tempRow = currentNode -> row;
    //      tempCol = currentNode -> col;
    //      tempVal = currentNode -> value;

    //      currentNode -> row = swapNode -> row;
    //      currentNode -> col = swapNode -> col;
    //      currentNode -> value = swapNode -> value;

    //      swapNode -> row = tempRow;
    //      swapNode -> col = tempCol;
    //      swapNode -> value = tempVal;
    //  }