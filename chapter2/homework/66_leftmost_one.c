#include <stdio.h>

/* 
* Generate mask indicating leftmost 1 in x. Assume w=32. 
* For example, 0xFF00 -> 0x8000, and 0x6600 --> 0x4000. 
* If x = 0, then return 0. 
*/ 

int leftmost_one(unsigned x) {
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    return x & ~(x >> 1);
}

int main() {
    printf("%d\n", leftmost_one(0x6600) == 0x4000);
    return 0;
}