#include <stdio.h>
#include <ctime>
#include <Windows.h>

#define SECOND 10000000
int counter = 0;

DWORD function()
{
	clock_t start = clock();

	for (int i = 0;;i++) 
	{
		if ((double)(clock() - start) / CLOCKS_PER_SEC >= 15)
		{
			printf("15 seconds - %d iterations", counter);
			return 0;
		}

		counter++;
	}
}

int main() 
{
	HANDLE timer = CreateWaitableTimerA(NULL, FALSE, NULL);
	long long startTime = -3 * SECOND;

	HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)function, NULL, 0, NULL);

	printf("0 seconds - %d iterations\n", counter);

	for (int i = 1; i <= 4; i++)
	{	
		if (!SetWaitableTimer(timer, (LARGE_INTEGER*)&startTime, 0, NULL, NULL, FALSE)) 
		{
			throw "Error SetWaitableTimer";
		}

		WaitForSingleObject(timer, INFINITE);
		
		printf("%d seconds - %d iterations\n", i * 3, counter);
	}
	CloseHandle(timer);

	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);

	return 0;
}