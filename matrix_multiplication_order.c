#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdbool.h>
#include <string.h>
#include <ctype.h>

double randomNumber() {
    return (double)rand() / (double)RAND_MAX;
}

double **randomSquareMatrix(int N) {
    double **matrix = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (double *)malloc(N * sizeof(double));   
        for (int j = 0; j < N; j++) matrix[i][j] = randomNumber();
    };
    return matrix;
}

double *randomVector(int N) {
    double *vector = (double *)malloc(N * sizeof(double));
    for (int i = 0; i <= N; i++) vector[i] = 0;

    return vector;
}


double *emptyVector(int N) {
    double *vector = (double *)malloc(N * sizeof(double));
    for (int i = 0; i <= N; i++) vector[i] = 0;

    return vector;
}

double *matrixVectorMultiplyij(double **matrix, double *vector, int N) {
    double *result = emptyVector(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) result[i] += matrix[i][j] * vector[j];
    }
    return result;
}

double *matrixVectorMultiplyji(double **matrix, double *vector, int N) {
    double *result = emptyVector(N);

    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) result[i] += matrix[i][j] * vector[j];
    }
    return result;
}


int main() {

    FILE *ij, *ji;

    ij = fopen("./results/c_IJ.csv", "w+");
    ji = fopen("./results/c_JI.csv", "w+");


    for (int i = 1; i <= 33; i++){
        int N = 1000 * i;
    
        // create the matrix and vectors and fill them with random numbers or empty
        double **matrix = randomSquareMatrix(N);
        double *vector  = randomVector(N);
        double *result;

        // multiply the matrix and vector print the time taNen

        // IJ
        clock_t start, finish;
        start = clock();

        result = matrixVectorMultiplyij(matrix, vector, N);

        finish = clock();
        
        
        double time_taken = ((double)(finish - start)) / CLOCKS_PER_SEC;;  // in seconds

        printf("For size %d, the matrix multiplication IJ took %.6f second(s) to execute \n", N, time_taken);
        fflush(ij);
        fprintf(ij, "%d, %.6f\n", N, time_taken);


        // JI
        start = clock();

        result = matrixVectorMultiplyji(matrix, vector, N);

        finish = clock();

        time_taken = ((double)(finish - start)) / CLOCKS_PER_SEC;;  // in seconds

        printf("For size %d, the matrix multiplication JI took %.6f second(s) to execute \n", N, time_taken);
        fprintf(ji, "%d, %.6f\n", N, time_taken);
    }
    fclose(ij);
    fclose(ji);

    

    return 0;
}
