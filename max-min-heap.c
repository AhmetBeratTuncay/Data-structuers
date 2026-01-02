#include <stdio.h>
#include <stdlib.h>

#define CAP 128

typedef struct {
    int a[CAP];
    int n;
    int is_min; 
} Heap;

int better(Heap *h, int x, int y) {
    return h->is_min ? (x < y) : (x > y);
}

void heap_init(Heap *h, int is_min) { h->n = 0; h->is_min = is_min; }

void heap_swap(int *x, int *y){ int t=*x; *x=*y; *y=t; }

void heap_push(Heap *h, int v) {
    if (h->n >= CAP) return;
    int i = h->n++;
    h->a[i] = v;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (better(h, h->a[i], h->a[p])) {
            heap_swap(&h->a[i], &h->a[p]);
            i = p;
        } else break;
    }
}

void heapify_down(Heap *h, int i) {
    while (1) {
        int l = 2*i + 1, r = 2*i + 2;
        int best = i;
        if (l < h->n && better(h, h->a[l], h->a[best])) best = l;
        if (r < h->n && better(h, h->a[r], h->a[best])) best = r;
        if (best != i) {
            heap_swap(&h->a[i], &h->a[best]);
            i = best;
        } else break;
    }
}

int heap_pop(Heap *h, int *ok) {
    if (h->n == 0) { if (ok) *ok = 0; return 0; }
    if (ok) *ok = 1;
    int root = h->a[0];
    h->a[0] = h->a[--h->n];
    heapify_down(h, 0);
    return root;
}

void heap_print(Heap *h) {
    for (int i = 0; i < h->n; i++) printf("%d ", h->a[i]);
    printf("\n");
}

int main(void) {
    int vals[] = {10, 4, 15, 20, 0, 8, 7};
    int m = (int)(sizeof(vals)/sizeof(vals[0]));

    Heap maxh, minh;
    heap_init(&maxh, 0);
    heap_init(&minh, 1);

    for (int i = 0; i < m; i++) {
        heap_push(&maxh, vals[i]);
        heap_push(&minh, vals[i]);
    }

    printf("MaxHeap array: "); heap_print(&maxh);
    printf("MinHeap array: "); heap_print(&minh);

    int ok;
    printf("Pop Max: %d\n", heap_pop(&maxh, &ok));
    printf("Pop Min: %d\n", heap_pop(&minh, &ok));

    printf("After pop MaxHeap: "); heap_print(&maxh);
    printf("After pop MinHeap: "); heap_print(&minh);
    return 0;
}
