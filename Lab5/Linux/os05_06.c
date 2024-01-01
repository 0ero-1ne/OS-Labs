#include <stdio.h>
#include <unistd.h>

int main()
{
    for (int i = 0; i < 10000; i++)
    {
        printf("%d - %d\n", getpid(), i);
        sleep(1);
    }
}