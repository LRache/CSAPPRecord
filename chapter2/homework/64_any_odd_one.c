#include <stdio.h>

// 2.64 Return 1 when any odd bit of x equals 1; 0 otherwise. Assume w=32
int any_odd_one(unsigned int x) {
    return !!(x & 0xAAAAAAAA);
}

int main() {
    printf("%d\n", any_odd_one(0xAAAAAAAA));
    return 0;
}