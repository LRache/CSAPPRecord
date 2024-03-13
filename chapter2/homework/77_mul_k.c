#include <stdio.h>

int mul_17(int x) {
    return x << 4 + x;
}

int mul_neg_7(int x) {
    return x - x >> 3;
}

int mul_60(int x) {
    return x << 6 - x << 2;
}

int mul_neg_112(int x) {
    return x << 4 - x << 7;
}

int main() {
    printf("%d\n", mul_17(1) == 17);
    printf("%d\n", mul_neg_7(2) == -14);
    
    return 0;
}
