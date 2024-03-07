// 2.58 is_little_endian
#include <stdio.h>

int is_little_endian() {
    int number = 1;
    char *ptr = (char*)&number;
    return *ptr != 0;
}

int main() {
    printf("%d", is_little_endian());
    return 0;
}