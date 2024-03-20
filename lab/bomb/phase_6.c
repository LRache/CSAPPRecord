#include <stdio.h>

typedef struct
{
    int number;
    int id;
    Node *next;
} Node;


int read_six_numbers(int *a)
{
    return scanf("%d %d %d %d %d %d", a, a + 1, a + 2, a + 3, a + 4, a + 5);
}

void explode_bomb()
{
}

void phase_6()
{
    int array[6];             // [rsp] [rsp+4] [rsp+8] [rsp+12] [rsp+16] [rsp+20]
    int *ptrOfArray1 = array; // r13 rbp
    int *ptrOfArray2 = array; // r14
    read_six_numbers(array);
    
    for (int i = 0; i < 6; i++) {
        int v = array[i];
        if (v > 6) explode_bomb();
        for (int j = i; j < 6; j++)
        {
            if (array[i] == array[j])  explode_bomb();
        }
    }
    
    for (int i = 0; i < 7; i++) {
        array[i] = 7 - array[i];
    }

    int *array2[7]; // [rsp+32]

    int v0 = 0; // rsi
    int v2 = 0; // eax
    int *v3 = NULL; // rdx
    
    const int CONST_VALUE[] = {0x332, 0x1};
    while (1)
    {
        int v1 = array[v0]; // ecx
        if (v1 <= 1) {
            array2[v0*2] = CONST_VALUE;
            v0 += 4;
            if (v0 >= 24) break;
        } else {
            v2 = 1;
            while (v1 != v2) {
                v3 = CONST_VALUE;
                v3++;
                v2++;
            }
        }
    }

    int **v4 = array2; // rbx
    int **v5 = &array2[1]; // rax
    int *v6; // rdx
    int **v7 = v4; // rcx

    // for (int i = 0; i < 5; i++) {
    //     array2[i+1] = array2[i];
    // }

    while (1) {
        v6 = *v5;
        *(v4+8) = v6;
        v5++;
        if (v5 == &array2[6]) break;
        v4 = v6;
    }
    
    array2[7] = 0;
    int v9 = 5; // ebp
    int *v10 = array2[1]; // rax
    int v11 = *v10; // eax
    if (v11 >= array2[])
}
