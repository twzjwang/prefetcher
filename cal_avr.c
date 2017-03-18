#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc <= 1)
        return 0;
    int n = strtol(argv[1], NULL, 10);
    long sum = 0, temp;
    int i;

    FILE *fp = fopen("NAI_out.txt", "r");
    for (i = 0; i < n; i++) {
        fscanf(fp, "%ld", &temp);
        sum += temp;
    }
    fclose(fp);
    printf("\nnaive_transpose         : %6ld us\n", sum/n);

    sum = 0;
    fp = fopen("SSE_out.txt", "r");
    for (i = 0; i < n; i++) {
        fscanf(fp, "%ld", &temp);
        sum += temp;
    }
    fclose(fp);
    printf("sse_transpose           : %6ld us\n", sum/n);

    sum = 0;
    fp = fopen("SSE_PF_out.txt", "r");
    for (i = 0; i < n; i++) {
        fscanf(fp, "%ld", &temp);
        sum += temp;
    }
    fclose(fp);
    printf("sse_prefetch_transpose  : %6ld us\n", sum/n);

    sum = 0;
    fp = fopen("AVX_out.txt", "r");
    for (i = 0; i < n; i++) {
        fscanf(fp, "%ld", &temp);
        sum += temp;
    }
    fclose(fp);
    printf("AVX_transpose           : %6ld us\n", sum/n);
    return 0;
}
