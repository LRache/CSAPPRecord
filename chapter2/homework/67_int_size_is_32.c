#include <stdio.h>

int int_size_is_32() {
    int x = 1;
    x <<= 15;
    x <<= 1;
    x <<= 15;
    return !(x<<1) && (x);
}

int main() {
    printf("%d\n", int_size_is_32());
}