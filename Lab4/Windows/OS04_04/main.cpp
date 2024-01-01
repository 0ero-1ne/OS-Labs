#include <iostream>
#include <Windows.h>

DWORD process_id;

DWORD WINAPI firstThreadFunction()
{
	DWORD thread_id = GetCurrentThreadId();

	for (int i = 0; i < 50; i++)
	{
		if (i == 24) Sleep(10000);
		std::cout << "OS04_04_T1: " << process_id << " - " << thread_id << std::endl;
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI secondThreadFunction()
{
	DWORD thread_id = GetCurrentThreadId();

	for (int i = 0; i < 125; i++)
	{
		if (i == 79) Sleep(15000);
		std::cout << "OS04_04_T2: " << process_id << " - " << thread_id << std::endl;
		Sleep(1000);
	}

	return 0;
}

int main()
{
	process_id = GetCurrentProcessId();
	DWORD thread_id = GetCurrentThreadId();

	HANDLE handleChildThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)firstThreadFunction, NULL, 0, NULL);
	HANDLE handleChildThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)secondThreadFunction, NULL, 0, NULL);

	for (int i = 0; i < 100; i++)
	{
		if (i == 29) Sleep(10000);
		std::cout << "OS04_04: " << process_id << " - " << thread_id << std::endl;
		Sleep(1000);
	}

	WaitForSingleObject(handleChildThread1, INFINITE);
	WaitForSingleObject(handleChildThread2, INFINITE);
	CloseHandle(handleChildThread1);
	CloseHandle(handleChildThread2);

	return 0;
}