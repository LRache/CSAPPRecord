#include <stdio.h>

int read_six_numbers(int *a)
{
    return scanf("%d %d %d %d %d %d", a, a + 1, a + 2, a + 3, a + 4, a + 5);
}

void explode_bomb()
{
}

void phase_6()
{
    int array[6];             // [rsp]
    int *ptrOfArray1 = array; // r13 rbp
    int *ptrOfArray2 = array; // r14
    read_six_numbers(array);
    int v0 = 0; // r12d
    for (int i = 0; i < 6; i++) {
        int v = array[i];
        if (v > 6) explode_bomb();
        for (int j = i; j < 6; j++)
        {
            if (array[i] == array[j]) 
            explode_bomb();
        }
    }
    
}
