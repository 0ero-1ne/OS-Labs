#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("PID = %d\n", getpid());

    void* memory = malloc(1024 * 1024 * 256);

	printf("Malloc = %p\n", memory);

	sleep(120);

    return 0;
}