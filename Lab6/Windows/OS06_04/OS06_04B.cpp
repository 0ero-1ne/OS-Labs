#include <iostream>
#include <Windows.h>

int main()
{
	HANDLE semaphore = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, (LPCSTR) "OS06_04");

	for (int i = 0; i < 90; i++)
	{
		if (i == 30)
			WaitForSingleObject(semaphore, INFINITE);

		else if (i == 60)
			ReleaseSemaphore(semaphore, 1, NULL);

		printf("OS06_04B - %d\n", i);
		Sleep(100);
	}

	CloseHandle(semaphore);
	system("pause");
	return 0;
}