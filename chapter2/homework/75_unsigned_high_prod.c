#include <stdio.h>
#include <limits.h>

int signed_high_prod(int x, int y) {
    long long r = (long long)x * y;
    return r >> 32;
}

int unsigned_high_prod(unsigned x, unsigned y) {
    return (signed_high_prod(x, y) + (x>>31) * y + (y>>31) * x);
}

int unsigned_high_prod_(unsigned x, unsigned y) {
    unsigned long long r = (unsigned long long) x * y;
    return r >> 32;
}

int main() {
    printf("%d\n", unsigned_high_prod(INT_MAX, INT_MAX) == unsigned_high_prod_(INT_MAX, INT_MAX));
    printf("%d\n", unsigned_high_prod(INT_MIN, INT_MIN) == unsigned_high_prod_(INT_MIN, INT_MIN));
    printf("%d\n", unsigned_high_prod(0x0302, 0x0204) == unsigned_high_prod_(0x0302, 0x0204));
    return 0;
}
