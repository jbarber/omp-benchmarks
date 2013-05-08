#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X_SIZE 1000
#define Y_SIZE 1000
#define Z_SIZE 1000
#define TRANS(x,y,z) (x + y * Y_SIZE + z * Z_SIZE * Y_SIZE)

int * alloc_mat (const int x, const int y, const int z) {
    int *mat = malloc(sizeof(int) * x * y * z);
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

    #pragma omp parallel for default(shared)
    for (int i = 0; i < X_SIZE; i++) {
        #pragma omp parallel for default(shared) private(i)
        for (int j = 0; j < Y_SIZE; j++) {
            #pragma omp parallel for default(shared) private(i,j)
            for (int k = 0; k < Z_SIZE; k++) {
                tar_mat[TRANS(i,j,k)] = src_mat[TRANS(i,j,k)];
            }
        }
    }

    free_mat(src_mat);
    free_mat(tar_mat);
}
