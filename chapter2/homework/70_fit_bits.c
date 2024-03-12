#include <stdio.h>

#define w (sizeof(int)<<3)

int fit_bits(int x, int n){
    int y = x;
    y <<= (w-n);
    y >>= (w-n);
    return x == y;
}

int main() {
    printf("%d\n", fit_bits(0b1001, 5));
    printf("%d\n", fit_bits(0b1001, 4));
    printf("%d\n", fit_bits(0b1001, 3));
    return 0;
}
