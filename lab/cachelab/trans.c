/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

void transpose_32x32(int A[32][32], int B[32][32])
{
    for (int i = 0; i < 32; i += 8)
    {
        for (int j = 0; j < 32; j += 8)
        {
            for (int k = 0; k < 8; k++)
            {
                int tmp0 = A[i + k][j];
                int tmp1 = A[i + k][j + 1];
                int tmp2 = A[i + k][j + 2];
                int tmp3 = A[i + k][j + 3];
                int tmp4 = A[i + k][j + 4];
                int tmp5 = A[i + k][j + 5];
                int tmp6 = A[i + k][j + 6];
                int tmp7 = A[i + k][j + 7];
                B[j][i + k] = tmp0;
                B[j + 1][i + k] = tmp1;
                B[j + 2][i + k] = tmp2;
                B[j + 3][i + k] = tmp3;
                B[j + 4][i + k] = tmp4;
                B[j + 5][i + k] = tmp5;
                B[j + 6][i + k] = tmp6;
                B[j + 7][i + k] = tmp7;
            }
        }
    }
}

void transpose_64x64(int A[64][64], int B[64][64]) {
    for (int i = 0; i < 64; i += 8) {
        for (int j = 0; j < 64; j += 8) {
            // for (int k = 0; k < 4; k++) {
            //     for (int l = 0; l < 4; l++) {
            //         B[j+l][i+k] = A[i+k][j+l];
            //     }
            // }
            // // 
            // for (int k = 0; k < 4; k++) {
            //     for (int l = 0; l < 4; l++) {
            //         B[j+k][i+l+4] = A[i+k][j+l+4];
            //     }
            // }
            for (int k = 0; k < 4; k++) {
                 // trans A top|left to B top|left and move A top|right to B top|right
                int tmp0 = A[i+k][j+0];
                int tmp1 = A[i+k][j+1];
                int tmp2 = A[i+k][j+2];
                int tmp3 = A[i+k][j+3];
                int tmp4 = A[i+k][j+4];
                int tmp5 = A[i+k][j+5];
                int tmp6 = A[i+k][j+6];
                int tmp7 = A[i+k][j+7];
                B[j+0][i+k] = tmp0;
                B[j+1][i+k] = tmp1;
                B[j+2][i+k] = tmp2;
                B[j+3][i+k] = tmp3;
                B[j+0][i+k+4] = tmp4;
                B[j+1][i+k+4] = tmp5;
                B[j+2][i+k+4] = tmp6;
                B[j+3][i+k+4] = tmp7;
            }
            for (int k = 0; k < 4; k++) { // k for row index of matrix B
                // get B top|right 2
                int tmp0 = B[j+k][i+4];
                int tmp1 = B[j+k][i+5];
                int tmp2 = B[j+k][i+6];
                int tmp3 = B[j+k][i+7];
                // get A bottom|left 3
                int tmp4 = A[i+4][j+k];
                int tmp5 = A[i+5][j+k];
                int tmp6 = A[i+6][j+k];
                int tmp7 = A[i+7][j+k];
                // trans A bottom|left 3 to B top|right 2
                B[j+k][i+4] = tmp4;
                B[j+k][i+5] = tmp5;
                B[j+k][i+6] = tmp6;
                B[j+k][i+7] = tmp7;
                // move B top|right 2 to B bottom|left 3
                B[j+k+4][i+0] = tmp0;
                B[j+k+4][i+1] = tmp1;
                B[j+k+4][i+2] = tmp2;
                B[j+k+4][i+3] = tmp3; 
            }
            // trans A bottom|right to B top|right
            // for (int k = 0; k < 4; k++) {
            //     // int tmp4 = A[i+k+4][j+0];
            //     // int tmp5 = A[i+k+4][j+1];
            //     // int tmp6 = A[i+k+4][j+2];
            //     // int tmp7 = A[i+k+4][j+3];
            //     // B[j+0][i+k+4] = tmp4;
            //     // B[j+1][i+k+4] = tmp5;
            //     // B[j+2][i+k+4] = tmp6;
            //     // B[j+3][i+k+4] = tmp7;
            // }
            // trans A right|bottom to B right bottom
            for (int k = 4; k < 8; k++) {
                int tmp0 = A[i+k][j+4];
                int tmp1 = A[i+k][j+5];
                int tmp2 = A[i+k][j+6];
                int tmp3 = A[i+k][j+7];
                B[j+4][i+k] = tmp0;
                B[j+5][i+k] = tmp1;
                B[j+6][i+k] = tmp2;
                B[j+7][i+k] = tmp3;
            }
        }
    }
}

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 && N == 32)
    {
        transpose_32x32(A, B);
        return;
    }
    if (M == 64 && N == 64) {
        transpose_64x64(A, B);
        return;
    }

#define BLOCK_SIZE 17
    for (int i = 0; i < N; i+=BLOCK_SIZE) {
        for (int j = 0; j < M; j+=BLOCK_SIZE) {
            int ek = i + BLOCK_SIZE;
            int el = j + BLOCK_SIZE;
            for (int k = i; k < ek && k < N; k++) {
                for (int l = j; l < el && l < M; l++) {
                    B[l][k] = A[k][l];
                }
            }
        }
    }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
