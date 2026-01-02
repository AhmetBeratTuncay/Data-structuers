#include <stdio.h>

#define CAP 64

int insert_at(int a[], int *n, int pos, int val){
    if (*n >= CAP) return 0;
    if (pos < 0 || pos > *n) return 0;
    for (int i = *n; i > pos; i--) a[i] = a[i-1];
    a[pos] = val;
    (*n)++;
    return 1;
}

int delete_at(int a[], int *n, int pos){
    if (*n <= 0) return 0;
    if (pos < 0 || pos >= *n) return 0;
    for (int i = pos; i < *n - 1; i++) a[i] = a[i+1];
    (*n)--;
    return 1;
}

void print_arr(int a[], int n){
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main(void){
    int a[CAP] = {1,2,3,4,5};
    int n = 5;

    printf("Start: "); print_arr(a, n);

    insert_at(a, &n, 2, 99); 
    printf("After insert: "); print_arr(a, n);

    delete_at(a, &n, 4); 
    printf("After delete: "); print_arr(a, n);

    return 0;
}
