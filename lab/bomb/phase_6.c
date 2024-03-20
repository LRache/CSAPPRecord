#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
    int number;
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
    Node *begin = NULL, *last = NULL;
    Node *nodeMemory[6];
    int values[] = {0x14c, 0x0a8, 0x39c, 0x2b3, 0x1dd, 0x1bb};
    for (int i = 0; i < 6; i++)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        nodeMemory[i] = node;
    }

    int array[6];             // [rsp] [rsp+4] [rsp+8] [rsp+12] [rsp+16] [rsp+20]
    Node *nodeArray[6];       // [rsp+32]
    int *ptrOfArray1 = array; // r13
    int *ptrOfArray2 = array; // r14
    read_six_numbers(array);

    // int v0 = 0; // r12d
    // while(1) {
    //     int v1 = *ptrOfArray1; // eax
    //     v1--;
    //     if (v1 > 5) {
    //         explode_bomb();
    //     }
    //     v0++;
    //     if (v0 == 6) break;
    //     while (1) {
    //         int v1 = v0; // ebx
    //         int v2 = array[v0];
    //         if (v2 == *ptrOfArray1) explode_bomb();
    //         v1++;
    //         if (v1 > 5) break;
    //     }
    //     ptrOfArray1++;
    // }

    int i = 0;
    while (1)
    {
        if (array[i] > 6)
            explode_bomb();
        i++;
        if (i == 6)
            break;
        for (int j = i; j < 6; j++)
        {
            if (array[i] == array[j])
                explode_bomb();
        }
    }

    // phase_6 + 95

    // int *v0 = &array[6]; // rsi
    // int *v1 = &array[0]; // rax
    // while(1) {
    // int v2 = 7; // ecx
    //     int v3 = v2; // edx
    //     v3 = v3 - *v1;
    //     *v1 = v3;
    //     v1++;
    //     if (v1 != v0) break;
    // }
    for (int i = 0; i < 6; i++)
    {
        array[i] = 7 - array[i];
    }

    // phase_6 + 123
    // int v0 = 0; // rsi

    // phase_6 + 163
    // while(1) {
    //     int v1 = array[v0]; // ecx
    //     Node *v3 = nodeMemory; // rdx

    //     if (v1 > 1) {
    //         int v2 = 1; // eax
    //         // phase_6 + 130
    //         while (v1 != v2) {
    //             v3++;
    //             v2++;
    //         }
    //     }

    //     // phase_6 + 148
    //     nodeArray[v0] = v3;
    //     v0++;
    //     if (v0 == 6) break;
    // }

    for (int i = 0; i < 6; i++)
    {
        int j = 0; // Node *v = nodeMemory;
        if (array[i] > 1)
        {
            // int k = 1;
            // if (k != array[i])
            // {
            //     j++;
            //     k++;
            // }
            j = array[i]-1;
        }
        nodeArray[i] = nodeMemory[j];
    }

    // phase_6 + 183
    // Node *v0 = nodeArray[0];   // rbx
    // Node **v1 = &nodeArray[1]; // rax
    // Node **v2 = &nodeArray[6]; // rsi
    // Node *v3 = v0; // rcx
    // Node *v4 = NULL;
    // while (1)
    // {
    //     v4 = *v1; // rdx
    //     v3->next = v4;
    //     v1++;
    //     if (v1 == v2)
    //         break;
    //     v3 = v4;
    // }
    // v4->next = NULL;

    Node *node = nodeArray[0];
    for (int i = 0; i < 5; i++) {
        nodeArray[i]->next = nodeArray[i+1];
    }
    nodeArray[5]->next = NULL;
    
    // phase_6 + 222
    // int v5 = 5; // ebp
    // while (1)
    // {
    //     Node *v6 = v0->next; // rax
    //     if (v0->value < v6->value) explode_bomb();
    //     v0 = v0->next;
    //     v5--;
    //     if (v5 == 0) break;
    // }
    Node *node = nodeArray[0];
    for (int i = 0; i < 5; i++) {
        Node *next = node->next;
        if (node->value < next->value) explode_bomb();
        node = node->next;
    }

    for (int i = 0; i < 6; i++) {
        free(nodeMemory[i]);
        nodeMemory[i] = NULL;
    }
}
