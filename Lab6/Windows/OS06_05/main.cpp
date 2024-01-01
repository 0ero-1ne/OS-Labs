#include <iostream>
#include <Windows.h>

int main()
{
	STARTUPINFO si1;
	STARTUPINFO si2;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;

	ZeroMemory(&si1, sizeof(STARTUPINFO));
	ZeroMemory(&si2, sizeof(STARTUPINFO));

	si1.cb = sizeof(STARTUPINFO);
	si2.cb = sizeof(STARTUPINFO);

	HANDLE event;

	CreateProcess(L"C:\\������\\������������ �������\\Lab6\\Windows\\OS06_05\\os06_05a.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1);
	CreateProcess(L"C:\\������\\������������ �������\\Lab6\\Windows\\OS06_05\\os06_05b.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2);

	event = CreateEvent(NULL, FALSE, FALSE, L"OS06_05");

	for (int i = 1; i <= 90; i++)
	{
		if (i == 15)
			SetEvent(event);

		printf("OS06_05 - %d\n", i);
		Sleep(100);
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	CloseHandle(event);

	system("pause");

	return 0;
}