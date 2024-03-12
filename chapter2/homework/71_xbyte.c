#include <stdio.h>

// Declaration of data type where 4 bytes are packed into an unsigned
typedef unsigned packed_t; 
// Extract byte from word. Return as signed integer 
int xbyte(packed_t word, int bytenum) {
    int t = 
    word <<= ((3-bytenum) << 3);
    return ((int)word) >> (3 << 3);
}

int main() {
    printf("%d\n", xbyte(0x88888888, 1) == 0xffffff88);
    printf("%d\n", xbyte(0x12345678, 2) == 0x34);
    return 0;
}