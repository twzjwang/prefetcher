#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <assert.h>
//#include <xmmintrin.h>
#include <immintrin.h>
#include <malloc.h>
#include "impl.c"

int main(int argc, char **argv)
{
    if(argc <= 1)
        return 0;
    int n = strtol(argv[1], NULL, 10);
    if(n < 8)
        n = 8;
    printf("verify %d x %x matrix transpose\n", n, n);

    int i, j, k;
    int *testin;
    int *testout;
    int *expected;

    testin = memalign(4, n * n * sizeof(int));
    testout = memalign(4, n * n * sizeof(int));
    expected = memalign(4, n * n * sizeof(int));

    k = 0;
    printf("testin\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            testin[i*n+j] = k++;
            printf("%3d ", testin[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");

    k = 0;
    printf("expected\n");
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            expected[i*n+j] = k++;
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d ", expected[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");

    naive_transpose(testin, testout, n, n);
    printf("naive_transpose : ");
    if ( memcmp( testout, expected, n * n * sizeof(int)) == 0)
        printf("correct\n");
    else
        printf("incorrect\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d ", testout[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");

    sse_transpose(testin, testout, n, n);
    printf("sse_transpose : ");
    if ( memcmp( testout, expected, n * n * sizeof(int)) == 0)
        printf("correct\n");
    else
        printf("incorrect\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d ", testout[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");

    sse_prefetch_transpose(testin, testout, n, n);
    printf("sse_prefetch_transpose : ");
    if ( memcmp( testout, expected, n * n * sizeof(int)) == 0)
        printf("correct\n");
    else
        printf("incorrect\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d ", testout[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");
    sse_transpose_256(testin, testout, n, n);
    printf("sse_transpose_256 : ");
    if ( memcmp( testout, expected, n * n * sizeof(int)) == 0)
        printf("correct\n");
    else
        printf("incorrect\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d ", testout[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");

    free(testin);
    free(testout);
    free(expected);
    return 0;
}
