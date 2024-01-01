#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* function(void* name)
{
    for (int i = 1; i <= 90; i++)
    {
        if (i == 30)
            pthread_mutex_lock(&mutex);
        else if (i == 60)
            pthread_mutex_unlock(&mutex);

        printf("THREAD_%s - %d\n", (char*)name, i);
        usleep(100 * 1000);
    }

    pthread_exit("Child Thread");
}


int main(int argc, char* argv[])
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, NULL, function, (void*)"A");
    pthread_create(&thread2, NULL, function, (void*)"B");

    for (int i = 1; i <= 90; i++)
    {
        if (i == 30)
            pthread_mutex_lock(&mutex);
        else if (i == 60)
            pthread_mutex_unlock(&mutex);

        printf("THREAD_MAIN - %d\n", i);
        usleep(100 * 1000);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}