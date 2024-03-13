#include <stdio.h>
#include <limits.h>

#define IS_POSITIVE(x) (x&0x80000000)
#define IS_NEGITIVE(x) (!(x&0x80000000))

int tsub_ok(int x, int y) {
    int r = x - y;
    return !((IS_NEGITIVE(x) && IS_POSITIVE(y) && IS_POSITIVE(r)) || (IS_POSITIVE(x) && IS_NEGITIVE(y) && IS_NEGITIVE(r)));
}

int main() {
    printf("%d\n", tsub_ok(INT_MIN, 1));
    printf("%d\n", tsub_ok(INT_MAX, -1));
    printf("%d\n", tsub_ok(0x10, 0x20));
    return 0;
}
