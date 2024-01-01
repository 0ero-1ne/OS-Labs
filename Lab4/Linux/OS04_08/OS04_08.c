#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* OS04_07_T1(void* arg)
{
    printf("OS04_07_T1 started\n");

    for (int i = 0; i < 75; i++) {
        if (i == 50) sleep(10);

        printf("OS04_07_T1: %d - %d\n", i, getpid());
        sleep(1);
    }

    printf("OS04_07_T1 completed the work\n");

    pthread_exit(NULL);
}

int main()
{
    pthread_t TID;
    pthread_create(&TID, NULL, OS04_07_T1, NULL);

    printf("OS04_07 started\n");

    for (int i = 0; i < 100; i++) {
        if (i == 30) sleep(15);

        printf("OS04_07: %d - %d\n", i, getpid());
        sleep(1);
    }

    printf("OS04_07 completed the work\n");

    pthread_join(TID, NULL);

    return 0;
}