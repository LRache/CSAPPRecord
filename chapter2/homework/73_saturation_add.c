#include <stdio.h>
#include <limits.h>

int saturation_add(int x, int y) {
    int r = x + y;
    int signMask = 0x80000000;
    int pos = !(x & signMask) && !(y & signMask) && (r & signMask);
    int neg = (x & signMask) && (y & signMask) && !(r & signMask);
    (pos && (r = INT_MAX) || neg && (r = INT_MIN));
    return r;
}

int main() {
    printf("%d\n", saturation_add(INT_MAX, 1) == INT_MAX);
    printf("%d\n", saturation_add(INT_MIN, -1) == INT_MIN);
    printf("%d\n", saturation_add(0x10, 0x20) == 0x20);
    return 0;
}