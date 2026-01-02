#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, col, val;
} Triple;

typedef struct {
    int rows, cols;
    int nnz;        
    Triple *data;   
} SparseCOO;

void print_dense(int *A, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%3d ", A[i*c + j]);
        }
        printf("\n");
    }
}

SparseCOO dense_to_coo(int *A, int r, int c) {
    int nnz = 0;
    for (int i = 0; i < r*c; i++) if (A[i] != 0) nnz++;

    SparseCOO S;
    S.rows = r; S.cols = c; S.nnz = nnz;
    S.data = (Triple*)malloc(sizeof(Triple) * (size_t)nnz);

    int k = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int v = A[i*c + j];
            if (v != 0) {
                S.data[k++] = (Triple){i, j, v};
            }
        }
    }
    return S;
}

int* coo_to_dense(const SparseCOO *S) {
    int *A = (int*)calloc((size_t)S->rows * (size_t)S->cols, sizeof(int));
    for (int k = 0; k < S->nnz; k++) {
        Triple t = S->data[k];
        A[t.row * S->cols + t.col] = t.val;
    }
    return A;
}

void print_coo(const SparseCOO *S) {
    printf("COO (rows=%d, cols=%d, nnz=%d)\n", S->rows, S->cols, S->nnz);
    printf("row col val\n");
    for (int k = 0; k < S->nnz; k++) {
        printf("%3d %3d %3d\n", S->data[k].row, S->data[k].col, S->data[k].val);
    }
}

int main(void) {
    int r = 4, c = 5;
    int A[] = {
        0, 0, 3, 0, 4,
        0, 0, 5, 7, 0,
        0, 0, 0, 0, 0,
        0, 2, 6, 0, 0
    };

    printf("Dense matrix:\n");
    print_dense(A, r, c);

    SparseCOO S = dense_to_coo(A, r, c);
    printf("\nSparse form:\n");
    print_coo(&S);

    int *B = coo_to_dense(&S);
    printf("\nBack to dense:\n");
    print_dense(B, r, c);

    free(S.data);
    free(B);
    return 0;
}
