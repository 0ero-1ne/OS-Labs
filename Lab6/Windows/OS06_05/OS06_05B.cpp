#include <iostream>
#include <Windows.h>

int main()
{
	HANDLE event = OpenEventA(EVENT_ALL_ACCESS, FALSE, (LPCSTR) "OS06_05");

	WaitForSingleObject(event, INFINITE);
	SetEvent(event);

	for (int i = 1; i <= 90; i++)
	{
		printf("OS06_05B - %d\n", i);
		Sleep(100);
	}

	CloseHandle(event);

	system("pause");
	
    return 0;
}