#include <stdio.h>
#define w (sizeof(int)<<3)

int fun(u_int32_t x) {
    int flag = 0;
    flag |= !(x - 0xffffffff);
    flag |= !x;
    flag |= !((x >> (w-8)) - 0xff);
    flag |= !(x - 0xff);
    return flag;
}

int main() {
    printf("%d\n", fun(0xffffffff)); // 1
    printf("%d\n", fun(0x00000000)); // 1
    printf("%d\n", fun(0xff000000)); // 1
    printf("%d\n", fun(0x000000ff)); // 1
    printf("%d\n", fun(0x0000000f)); // 0
    return 0;
}