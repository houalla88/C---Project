#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define N 2032
#define NUM_THREADS 4 


typedef struct {
    int startRow;
    int endRow;
} ThreadData;

int *mat1, *mat2, *res;

int* allocateMatrix(int size) {
    return (int*)malloc(size * size * sizeof(int));
}

void freeMatrix(int* matrix) {
    free(matrix);
}

void *multiplyMatrices(void *arg) {
    ThreadData *data = (ThreadData*)arg;
    int i, j, k;

    for (i = data->startRow; i < data->endRow; i++) {
        for (j = 0; j < N; j++) {
            res[i * N + j] = 0;
            for (k = 0; k < N; k++) {
                res[i * N + j] += mat1[i * N + k] * mat2[j * N + k]; // Notez l'accès transposé à mat2
            }
        }
    }
    pthread_exit(NULL);
}

void writeTimeToFile(double time) {
    FILE *file = fopen("execution_time_c_opt.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(file, "Execution Time: %f seconds\n", time);
    fclose(file);
}

int main() {
    mat1 = allocateMatrix(N);
    mat2 = allocateMatrix(N);
    res = allocateMatrix(N);

  

    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];
    int thread, rc;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for(thread = 0; thread < NUM_THREADS; thread++) {
        threadData[thread].startRow = thread * (N / NUM_THREADS);
        threadData[thread].endRow = (thread + 1) * (N / NUM_THREADS);
        rc = pthread_create(&threads[thread], NULL, multiplyMatrices, (void *)&threadData[thread]);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(thread = 0; thread < NUM_THREADS; thread++) {
        pthread_join(threads[thread], NULL);
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    writeTimeToFile(cpu_time_used);
    printf("Execution Time: %f seconds\n", cpu_time_used);

    // Libération de la mémoire
    freeMatrix(mat1);
    freeMatrix(mat2);
    freeMatrix(res);

    pthread_exit(NULL);
}
