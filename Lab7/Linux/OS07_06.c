#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 

int main()
{
    struct timespec start, end;
    int counter = 0;

    clock_gettime(CLOCK_REALTIME, &start);
    for (;;)
    {
        counter++;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        if (end.tv_sec == 2)
        {
            printf("%ld seconds - %d iterations\n", end.tv_sec, counter);
            break;
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Real time = %ld.%d\n", end.tv_sec - start.tv_sec, abs(end.tv_nsec - start.tv_nsec));

    return 0;
}