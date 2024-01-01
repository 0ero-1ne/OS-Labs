#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>

int main()
{
    pid_t processId = getpid();
    pid_t threadId = gettid();
    int threadPriority = nice(0);

    printf("Process ID: --- %d ---\n", processId);
    printf("Thread ID: --- %d ---\n", threadId);
    printf("Thread priority: --- %d ---\n", threadPriority);

    cpu_set_t cpuSet;
    CPU_ZERO(&cpuSet);
    int cpuSize = 0;

    if (sched_getaffinity(0, sizeof(cpu_set_t), &cpuSet) == 0)
    {
        printf("Numbers of processors:\n");
        for (int i = 0; i < CPU_SETSIZE; i++)
        {
            if (CPU_ISSET(i, &cpuSet))
            {
                printf("%d\n", i);
            }
        }
    }
    else
    {
        printf("OS05_04: sched_getaffinity error");
    }

    return 0;
}