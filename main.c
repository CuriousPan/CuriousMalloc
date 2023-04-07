#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Malloc.h"

#define MY_MALLOC

typedef struct {
    int a;
    int b;
    int c;
    double d;
    float f;
} foo;

typedef struct {
    int a;
    double f;
    int b;
} bar;

typedef struct {
    bar b;
    foo f;

    double d;
    double dd;
    float ff;

    bar *bar_p;
} buzz;

int main()
{
#ifdef BEST_FIT
    printf("Best fit\n");
#else
    printf("First fit\n");
#endif
    clock_t begin = clock();

    bar *bar0 = c_malloc(sizeof(bar));

    int *int0 = c_malloc(sizeof(int));
    bar *bar1 = c_malloc(sizeof(bar));
    bar *bar2 = c_malloc(sizeof(bar));

    c_free(int0);

    int *int1 = c_malloc(sizeof(int));
    c_free(bar2);
    int *int2 = c_malloc(sizeof(int) * 8);

    buzz *buzz_arr = c_malloc(sizeof(buzz));

    c_free(buzz_arr);

    double* double0 = c_malloc(sizeof(double) * 35);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    dump_data();

    printf("It took: %f\n", time_spent);

    return 0;
}
