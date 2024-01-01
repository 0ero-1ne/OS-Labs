#include <stdio.h>
#include <Windows.h>
#include <ctime>

int count = 0, stopCounter = 0;

DWORD function()
{
    for (int i = 2;; i++)
    {
        if (stopCounter == 1)
        {
            break;
        }

        bool isPrime = true;

        for (int j = 2; j <= i/2; ++j) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime)
        {
            count++;
            printf("%d item - %d\n", count, i);
        }
    }
}

int main()
{
    HANDLE timer = OpenWaitableTimerW(TIMER_ALL_ACCESS, FALSE, L"TIMER");
    
	HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)function, NULL, 0, NULL);

    WaitForSingleObject(timer, INFINITE);
    stopCounter = 1;
    WaitForSingleObject(thread, INFINITE);

    return 0;
}