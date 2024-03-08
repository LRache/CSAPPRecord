#include <stdio.h>

#define w (sizeof(int)<<3)

unsigned int srl(unsigned int x, int k) {
    unsigned int xsra = (int) x >> k;
    unsigned int xsrl = xsra & ~(0xffffffff << (w-k));
    return xsrl;
}

int sra(int x, int k) {
    int xsrl = (unsigned int) x >> k;
    int xsra = xsrl + (((!(x & 0x80000000)) - 1) << (w-k));
    return xsra;    
}

int main() {
    unsigned int a = 0x12345678;
    printf("%d\n", srl(a, 5) == a >> 5);
    int b = 0x12345678;
    printf("%d\n", sra(b, 5) == b >> 5);
    return 0;
}