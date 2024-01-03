#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2032  // Matrix size, can be changed

// Function to dynamically allocate a matrix
int** allocateMatrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

// Function to free a dynamically allocated matrix
void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to multiply matrices
void multiplyMatrices(int** mat1, int** mat2, int** res, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            res[i][j] = 0;
            for (int k = 0; k < size; k++) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

// Function to write execution time to a file
void writeTimeToFile(double time) {
    FILE *file = fopen("execution_time.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(file, "Execution Time: %f seconds\n", time);
    fclose(file);
}

int main() {
    int **mat1, **mat2, **res;

    mat1 = allocateMatrix(N);
    mat2 = allocateMatrix(N);
    res = allocateMatrix(N);

    // Initialize matrices with some values (for example, 1)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mat1[i][j] = 1;
            mat2[i][j] = 1;
        }
    }

    // Measure execution time
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    multiplyMatrices(mat1, mat2, res, N);  // Perform matrix multiplication
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Write execution time to a file
    writeTimeToFile(cpu_time_used);

    printf("Execution Time: %f seconds\n", cpu_time_used);

    // Free allocated memory
    freeMatrix(mat1, N);
    freeMatrix(mat2, N);
    freeMatrix(res, N);

    return 0;
}
