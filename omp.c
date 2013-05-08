// gcc -fopenmp -O3 -g -std=c99 omp.c -o omp
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X_SIZE 1000
#define Y_SIZE 1000
#define Z_SIZE 1000
#define TRANS(z,y,x) (x + y * Y_SIZE + z * Z_SIZE * Y_SIZE)

int * alloc_mat (const int x, const int y, const int z) {
    const size_t size = sizeof(int) * x * y * z;
    int *mat = malloc(size);
    if (mat == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    return mat;
}

void free_mat (int *mat) {
    free(mat);
}

int main (int argc, char **argv) {
    int nthreads, tid;

    int *src_mat = alloc_mat(X_SIZE, Y_SIZE, Z_SIZE);
    int *tar_mat = alloc_mat(X_SIZE, Y_SIZE, Z_SIZE);

    memset(src_mat, 0x0, sizeof(int) * X_SIZE * Y_SIZE * Z_SIZE);
    memset(tar_mat, 0x0, sizeof(int) * X_SIZE * Y_SIZE * Z_SIZE);

    int i, j, k;
    #pragma omp parallel for shared(tar_mat) private(i,j,k) schedule(static,100)
    for (i = 0; i < X_SIZE; i++) {
        for (j = 0; j < Y_SIZE; j++) {
            for (k = 0; k < Z_SIZE; k++) {
#ifdef DEBUG
                printf("x:%i y:%i z:%i offset:%i\n", i, j, k, TRANS(i,j,k));
#endif
                tar_mat[TRANS(i,j,k)] = src_mat[TRANS(i,j,k)];
            }
        }
    }

    free_mat(src_mat);
    free_mat(tar_mat);
}
