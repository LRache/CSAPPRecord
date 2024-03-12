#include <stdio.h>

#define w (sizeof(int)<<3)

unsigned rotate_left(unsigned x, int n) {
    unsigned y = x;
    x <<= n;
    y >>= (w - n);
    unsigned mask = -1;
    mask >>= (w-n);
    return x | (y & mask);
}

int main() {
    printf("%d\n", rotate_left(0x12345678, 4) == 0x23456781);
    printf("%d\n", rotate_left(0x12345678, 20) == 0x67812345);
    return 0;
}