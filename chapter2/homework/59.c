#include <stdio.h>

u_int32_t fun(u_int32_t x, u_int32_t y) {
    return x & 0xff + y & 0xffffff00;
}

int main() {
    u_int32_t x = 0x89ABCDEF, y = 0x7654321;
    int r = fun(x, y);
    unsigned char *ptr = (unsigned char*)&x;
    for (int i = 0; i < 4; i++) {
        printf("%.2x", ptr[i]);
    }
    return 0;
}
