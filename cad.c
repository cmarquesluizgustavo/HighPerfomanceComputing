#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100


void randomSquareMatrix(double matrix[N][N]) {
    for  (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand();
}

void randomVector(double vector[N]) {
    for (int i = 0; i < N; i++)
        vector[i] = rand();
}

void emptyVector(double vector[N]) {
    for (int i = 0; i < N; i++)
        vector[i] = 0;
}

void matrixVectorMultiply(double matrix[N][N], double vector[N], double result[N]) {
    for (int i = 0; i < N; i++) {
        
        result[i] = 0;
        for (int j = 0; j < N; j++) result[i] += matrix[i][j] * vector[j];
    }
}


int main() {

    // create the matrix and vectors and fill them with random numbers or empty
    double matrix[N][N], vector[N], result[N];

    randomSquareMatrix(matrix);
    randomVector(vector);
    emptyVector(result);
    
    // multiply the matrix and vector print the time taNen
    clock_t time;
    time = clock();
    matrixVectorMultiply(matrix, vector, result);
    time = clock() - time;
    double time_taken = ((double)time) / CLOCKS_PER_SEC;  // in seconds
    printf("For size %d, the matrix multiplication took %f seconds to execute \n", N, time_taken);
    
    return 0;
}
