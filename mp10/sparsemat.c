#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{
    /*
     * ---------
     * GET NODES 
     * ---------
     */
    //initialize variables
    int rows, cols;
    int rowIndex, colIndex;
    double val;
    
    //start file
    FILE * myfile = fopen(input_file, "r");

    //set rows and cols of tuple
    fscanf(myfile, "%d %d", &rows, &cols);
    sp_tuples * myTuple = malloc(sizeof(sp_tuples));
    myTuple -> m = rows;
    myTuple -> n = cols;

    //initialize head node and next node. head node always points to null
    sp_tuples_node * headNode = NULL;
    sp_tuples_node * nextNode = NULL;

    do {
        //scan contents of 1 line into variables below
        fscanf(myfile, "%d %d %lf", &rowIndex, &colIndex, &val);
        //if val = 0 skip to next line
        if(val != 0){
            //allocate memory for the nextnode and set values of nextNode
            nextNode = malloc(sizeof(sp_tuples_node));
            nextNode -> row = rowIndex;
            nextNode -> col = colIndex;
            nextNode -> value = val;
            //point to headNode (aka NULL for the first term) since it is put at the end of the linked list
            nextNode -> next = headNode;
            myTuple -> nz += 1;
            //set headNode equal to the nextNode to save pointer to the nextNode
            headNode = nextNode;
        }  
    } while(fscanf(myfile, "%d %d %lf", &rowIndex, &colIndex, &val) != EOF);

    //close file and set tuple head to headNode
    fclose(myfile);
    myTuple -> tuples_head = headNode;

    /*
     * -----------
     * ORDER NODES
     * -----------
     */
    //currentNode keeps track of the current node that is being looked at in that moment of time
    sp_tuples_node * currentNode = myTuple -> tuples_head;
    //swapNode keeps track of the node to be swapped in that moment of time
    sp_tuples_node * swapNode = NULL;
    //testNode keeps track of the overall node from the head, to tail that is being checked for being in order
    sp_tuples_node * testedNode = myTuple -> tuples_head;

    //set up loop to overall loop through the whole tuple
    for(int i = 0; i < myTuple -> nz; i++){
        //if it isnt the first iteration, then increment the testedNode to the nextNode and set currentNode to that
        if(i != 0){
            testedNode = testedNode -> next;
            currentNode = testedNode;
        }
        //set swapNode which will go through the whole linked list to the beginning of the linked list
        swapNode = myTuple -> tuples_head;
        //loop through the linked list till NULL
        while(currentNode != NULL){
            //get the index of the current node (whatever node is being checked for, if 0th iteration then head node)
            int curNodeIndex = currentNode -> row * myTuple -> m + currentNode -> col;
            //get the index of the swap node, which is the head node on the 0th iteration
            int swapNodeIndex = swapNode -> row * myTuple -> m + swapNode -> col;
            //if the current node index > the index of the current node being checked, swap the values of those two nodes
            if(curNodeIndex > swapNodeIndex){
                int tempRow = currentNode -> row;
                int tempCol = currentNode -> col;
                double tempVal = currentNode -> value;

                currentNode -> row = swapNode -> row;
                currentNode -> col = swapNode -> col;
                currentNode -> value = swapNode -> value;

                swapNode -> row = tempRow;
                swapNode -> col = tempCol;
                swapNode -> value = tempVal;
            //else, increment to the next possible node in the linked list
            } else {
                swapNode = swapNode -> next;
            }
        }
    }
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



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    //segment to remove node from linked list if value is 0
    //set currentNode to head
    sp_tuples_node * currentNode = mat_t -> tuples_head;
    //set prevNode and nextNode to NULL for now
    sp_tuples_node * prevNode = NULL, * nextNode = NULL;
    //if value is 0, loop through linked list and look for corresponding row and column
    if(value == 0){
        while(currentNode != NULL){
            nextNode = currentNode -> next;
            if(currentNode -> row == row && currentNode -> col == col){
                //if prevNode is still NULL, we are at the beginning of the linked list
                if(prevNode == NULL){
                    //make the next node from the beginning, the new head
                    mat_t -> tuples_head = nextNode;
                    //free associated memory, set to NULL, and break
                    free(currentNode);
                    currentNode = NULL;
                    break;
                //if prevNode is not NULL, we are anywhere but the beginning of the linked list
                } else {
                    //set prevNode to point to the nextNode from the currnet node we are looking at
                    prevNode -> next = nextNode;
                    //free associated memory, set to NULL, and break
                    free(currentNode);
                    currentNode = NULL;
                    break;
                }
            // if the row and col doesnt match, set prevNode to the currentNode we just looked at and set currentNode to the next node
            } else {
                prevNode = currentNode;
                currentNode = currentNode -> next;
            }
        }
        //if the whole process works, then decrement nz since we now have one less value in our linked list
        mat_t -> nz -= 1;
    } 

    //segement to check if index is in linked list already AND value is non-zero
    //set currentNode back to the head
    currentNode = mat_t -> tuples_head;
    //loop through linked list till NULL is reached, if row and col match, set old value to new value and break
    while(currentNode != NULL){
        if(currentNode -> row == row && currentNode -> col == col){
            currentNode -> value = value;
            break;
        //else, increment to the next value in the linked list
        } else {
            currentNode = currentNode -> next;
        }
    } 
    //segment to ADDRESS if index is NOT in linked list already AND value is non-zero
    //set currentNode to the head of the matrix and prevNode back to NULL
    currentNode = mat_t -> tuples_head;
    prevNode = NULL;
    //loop through the linked list till NULL is reached
    while(currentNode != NULL){
        //get index of current node and index of the node you intend to place 
        int curNodeIndex = currentNode -> row * mat_t -> m + currentNode -> col;
        int swapNodeIndex = row * mat_t -> m + col;
        //if the prevNode is null, meaning we are at the head of the list, and the current index is greater
        //than what we want to insert, make what we want to insert the new head
        if(prevNode == NULL && curNodeIndex > swapNodeIndex){
            //allocate memory for new node and attach values passed through function
            sp_tuples_node * newHead = malloc(sizeof(sp_tuples_node));
            newHead -> row = row;
            newHead -> col = col;
            newHead -> value = value;
            //set mat_t head to this new head node
            mat_t -> tuples_head = newHead;
            //set the next value to the current node because that is no longer our head and this new head points to it
            newHead -> next = currentNode; 
            //if all this goes through, increment the number of values in this linked list by 1 since we added a node and break
            mat_t -> nz += 1;
            break;
        //if prevNode is not NULL, we are anywhere else in the linked list so insert the value in the proper spot
        } else {
            //if the current node index > the index of the node we want to insert, we put it before it
            if(curNodeIndex > swapNodeIndex){
                //allocate memory for new node and attach values passed through function
                sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
                newNode -> row = row;
                newNode -> col = col;
                newNode -> value = value;
                //make this new node point to our current node since it is being placed before it
                newNode -> next = currentNode;
                //update pointer of the old node that was behind current node to new node since it took its spot
                prevNode -> next = newNode;
                //if all this goes through, increment the number of values in this linked list by 1 since we added a node and break
                mat_t -> nz += 1;
                break;
            }
        }
        //if nothing works, then set prevNode to the currentNode we just checked and set currentNode to the next node in the linked list
        prevNode = currentNode;
        currentNode = currentNode -> next;
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



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
    sp_tuples * matC;
    if(matA -> m == matB -> m && matA -> n == matB -> n && matA != NULL && matB != NULL){
        matC = malloc(sizeof(sp_tuples));
        matC -> m = matA -> m;
        matC -> n = matA -> n;
        matC -> nz = 0;
        matC -> tuples_head = NULL;

        sp_tuples_node * currentNodeA = matA -> tuples_head;
        sp_tuples_node * currentNodeB = matB -> tuples_head;
        sp_tuples_node * prevNode;

        int curRowA, curColA, curRowB, curColB, i, j, sum;
        for(i = 0; i < matA -> nz; i++){
            currentNodeB = matB -> tuples_head;
            for(j = 0; j < matB -> nz; j++){
                curRowA = currentNodeA -> row;
                curColA = currentNodeA -> col;
                curRowB = currentNodeB -> row;
                curColB = currentNodeB -> col;

                if(curRowA == curRowB && curColA == curColB){
                    sum = currentNodeA -> value + currentNodeB -> value;
                    if(sum != 0){
                        if(matC -> nz == 0){
                            sp_tuples_node * headNode = malloc(sizeof(sp_tuples_node));
                            headNode -> row = curRowA;
                            headNode -> col = curColA;
                            headNode -> value = sum;

                            matC -> tuples_head = headNode;
                            headNode -> next = NULL;
                            prevNode = headNode;

                            matC -> nz += 1;
                        } else {
                            sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
                            newNode -> row = curRowA;
                            newNode -> col = curColA;
                            newNode -> value = sum;

                            prevNode -> next = newNode;
                            newNode -> next = NULL;
                            prevNode = newNode;

                            matC -> nz += 1;
                        }
                    }
                }
                currentNodeB = currentNodeB -> next;
            }
            currentNodeA = currentNodeA -> next;
        }
    } else {
        return NULL;
    }

    if(matC != NULL){
        return matC;
    }
	return NULL;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{ 
    
    return NULL; 
}


	
void destroy_tuples(sp_tuples * mat_t)
{
    //set currentNode to the head of the matrix and temp to NULL;
	sp_tuples_node * currentNode = mat_t -> tuples_head;
    sp_tuples_node * temp = NULL;
    //loop through linked list till NULL pointer is reached
    while(currentNode != NULL){
        //set temp node to next node in linked list
        temp = currentNode -> next;
        //free current node
        free(currentNode);
        //set current node to temp (the next node in the list)
        currentNode = temp;
    }
    //set current node to NULL after freeing the last node
    currentNode = NULL;
    //free the overall tuple object
    free(mat_t);
    //set tuple to NULL
    mat_t = NULL;
}  






