#include <iostream>
#include <Windows.h>

int main()
{
	HANDLE mutex = OpenMutexA(SYNCHRONIZE, FALSE, (LPCSTR) "OS06_03");

	for (int i = 1; i <= 90; ++i)
	{
		if (i == 30)
			WaitForSingleObject(mutex, INFINITE);

		else if (i == 60)
			ReleaseMutex(mutex);

		printf("OS06_03A - %d\n", i);
		Sleep(100);
	}

	CloseHandle(mutex);

	system("pause");
	return 0;
}