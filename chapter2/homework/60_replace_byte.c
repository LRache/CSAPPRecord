#include "show_bytes/show_bytes.h"
#include <stdio.h>
u_int32_t replace_byte(u_int32_t x, int i, unsigned char b) {
    u_int32_t t = 0b11111111;
    i *= sizeof(unsigned char);
    t <<= i;
    t = ~t;
    b <<= i;
    return (x & t) + b ;
}

int main() {
    u_int32_t r = replace_byte(0x12345678, 0, 0xAB);
    show_bytes((bytePtr)&r, 4);
}