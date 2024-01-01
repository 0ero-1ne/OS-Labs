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

	HANDLE mutex;

	CreateProcess(L"C:\\Univer\\OS\\Lab6\\Windows\\OS06_03\\os06_03a.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1);
	CreateProcess(L"C:\\Univer\\OS\\Lab6\\Windows\\OS06_03\\os06_03b.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2);

	mutex = CreateMutexA(NULL, FALSE, (LPCSTR)"OS06_03");

	for (int i = 1; i <= 90; ++i)
	{
		if (i == 30)
			WaitForSingleObject(mutex, INFINITE);

		else if (i == 60)
			ReleaseMutex(mutex);

		printf("OS06_03 - %d\n", i);
		Sleep(100);
	}


	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	CloseHandle(mutex);

	system("pause");

	return 0;
}