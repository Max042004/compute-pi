#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "computepi.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

#define COMPUTE_PI_ERROR(x) (((x > M_PI) ? (x - M_PI) : (M_PI - x)) / M_PI)

int main(int argc, char const *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    if (argc < 2)
        return -1;

    int N = atoi(argv[1]);
    int i, loop = 25;

#if defined(BASELINE)
    // Baseline
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_baseline(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf ", (double) (end.tv_sec - start.tv_sec) +
                       (end.tv_nsec - start.tv_nsec) / ONE_SEC);
    printf("%lf ", COMPUTE_PI_ERROR(compute_pi_baseline(N)));

    // OpenMP with 2 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_openmp(N, 2);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf ", (double) (end.tv_sec - start.tv_sec) +
                       (end.tv_nsec - start.tv_nsec) / ONE_SEC);
    printf("%lf ", COMPUTE_PI_ERROR(compute_pi_openmp(N, 2)));

    // OpenMP with 4 threads
    clock_gettime(CLOCK_ID, &start);
    for (i = 0; i < loop; i++) {
        compute_pi_openmp(N, 4);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf ", (double) (end.tv_sec - start.tv_sec) +
                       (end.tv_nsec - start.tv_nsec) / ONE_SEC);
    printf("%lf ", COMPUTE_PI_ERROR(compute_pi_openmp(N, 4)));
#endif

    return 0;
}
