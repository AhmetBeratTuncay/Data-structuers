#include <stdio.h>

void hanoi(int n, char from, char aux, char to) {
    if (n <= 0) return;
    hanoi(n - 1, from, to, aux);
    printf("Disk %d: %c -> %c\n", n, from, to);
    hanoi(n - 1, aux, from, to);
}

int main(void) {
    int n = 3;
    printf("Hanoi basliyor n=%d\n", n);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}
