#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t child_process = fork();

    if (child_process == 0) {
        char* args[] = {"./../OS03_05/OS03_05_1", NULL};
        execv(args[0], args);
    }
    else if (child_process > 0)
    {
        printf("OS03_07 started\n");
        for (int i = 0; i < 100; i++)
        {
            printf("OS03_07: %d - %d\n", i, getpid());
            sleep(1);
        }

        printf("OS03_07 complete the work\n");
    }
    else {
        perror("Fork create failed\n");
        return -1;
    }
    
    return 0;
}