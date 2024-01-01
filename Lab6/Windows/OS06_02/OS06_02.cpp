#include <iostream>
#include <Windows.h>

CRITICAL_SECTIos06ON criticalSection;

void WINAPI function(char* threadName)
{
    for (int i = 1; i <= 90; ++i)
	{
		if (i == 30)
			EnterCriticalSection(&criticalSection);

		printf("OS06_02_THREAD_%s\n", threadName);

		if (i == 60)
			LeaveCriticalSection(&criticalSection);

		Sleep(100);
	}
}

int main()
{
    int pid = GetCurrentProcessId();

	DWORD ChildId1 = NULL;
	DWORD ChildId2 = NULL;

	HANDLE threads[2];

	threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)function, (char*)"A", 0, &ChildId1);
	threads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)function, (char*)"B", 0, &ChildId1);


	InitializeCriticalSection(&criticalSection);

	function((char*)"Main");

	WaitForMultipleObjects(2, threads, TRUE, INFINITE);

	CloseHandle(threads[0]);
    CloseHandle(threads[1]);

	DeleteCriticalSection(&criticalSection);

	return 0;
}