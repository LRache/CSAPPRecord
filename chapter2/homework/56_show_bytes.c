#include <stdio.h>

typedef unsigned char *bytePtr;

void show_bytes(bytePtr start, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%.2x", start[i]);
    }
}

void test_show_bytes() {
    int number = 0x89ABCDEF;
    show_bytes((bytePtr)&number, sizeof(number));
}

int main(int argc, char const *argv[])
{
    test_show_bytes();
    return 0;
}
