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

	HANDLE semaphore;

	if (!CreateProcess(L"C:\\Univer\\OS\\Lab6\\Windows\\OS06_04\\os06_04a.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
	{
		std::cout << "Process did not created!\n";
		std::cout << GetLastError() << std::endl;
	}
	CreateProcess(L"C:\\Univer\\OS\\Lab6\\Windows\\OS06_04\\os06_04b.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2);

	semaphore = CreateSemaphoreW(NULL, 2, 2, L"OS06_04");

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
			WaitForSingleObject(semaphore, INFINITE);

		else if (i == 60)
			ReleaseSemaphore(semaphore, 1, NULL);

		printf("OS06_04 - %d\n", i);
		Sleep(100);
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	CloseHandle(semaphore);

	system("pause");

	return 0;
}