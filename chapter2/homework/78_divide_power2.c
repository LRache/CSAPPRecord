#include <stdio.h>

int divide_power2(int x, int k) {
    int bias = (x >> 31) & (1 << k-1);
    return (x + bias) >> k;
}

int main() {
    printf("%d\n", 0x102030 / 16 == divide_power2(0x102030, 4));
    printf("%d\n", 0x10203040 / 16 == divide_power2(0x10203040, 4));
    return 0;
}