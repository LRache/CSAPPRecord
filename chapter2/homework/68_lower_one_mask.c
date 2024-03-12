#include <stdio.h>

unsigned lower_one_mask(int n) {
    unsigned x = -1;
    x <<= n;
    return ~x;
}

int main() {
    printf("%d\n", lower_one_mask(6) == 0x3f);
    printf("%d\n", lower_one_mask(17) == 0x1ffff);
}
