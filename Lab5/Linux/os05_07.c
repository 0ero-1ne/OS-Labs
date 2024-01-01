#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t cpid = fork();

    if (cpid == 0)
    {
        int newNice = nice(10);
        for (int i = 0; i < 1000; i++)
        {
            printf("Child: %d - %d \n", i, getpid());
            sleep(1);
        }
        printf("Child process ended\n");
    }
    else if (cpid > 0)
    {
        for (int i = 0; i < 1000; i++)
        {
            printf("Parent: %d - %d \n", i, getpid());
            sleep(1);
        }
        printf("Parent process ended\n");
    }
    else
    {
        perror("Create child process error\n");
        return -1;
    }

    return 0;
}