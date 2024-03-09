#include <stdio.h>

// Return 1 when x contains an odd number of ls; 0 otherwise. Assume w=32
int odd_ones(unsigned int x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;
}

int main() {
    unsigned int x;
    scanf("%u", &x);
    printf("%d", odd_ones(x));
    return 0;
}