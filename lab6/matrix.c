/* Function matrix_multiply
 * matrixA, matrixB, and matrix C are matrices represented as
 * one-dimensional arrays in row-major order. This function must
 * preform matrix multiplication so that C=A*B. 
 * INPUT: matrixA, a one dimensional array of size m*k
 *        matrixB, a one dimensional double array of size k*n
 * OUTPUT: matrixC, a one dimensional double array of size m*n
 */
void matrix_multiply(double *matrixA,double *matrixB,double *matrixC,int m,int k,int n){

    int lengthC = m * n;

    // m is rows of A
    // n is columns of B

    for(int i = 0; i < lengthC; i++){
        for(int j = 0; j < k; j++){
            matrixC[i] += matrixA[i * k + j] * matrixB[i + n];
        }
    }

}