#include <stdio.h>

#define w (sizeof(int)<<3)

int int_shifts_are_arithmetic() {
    int x = -1;
    return (x >> w) & 1;
}

int main()
{
    printf("%d\n", int_shifts_are_arithmetic());
    return 0;
}
