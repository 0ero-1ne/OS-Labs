#include <iostream>
#include <Windows.h>

using namespace std;

DWORD setPriority(DWORD processPriority)
{
	switch (processPriority) {
		case 1:
			return IDLE_PRIORITY_CLASS;
		case 2:
			return BELOW_NORMAL_PRIORITY_CLASS;
		case 3:
			return NORMAL_PRIORITY_CLASS;
		case 4:
			return ABOVE_NORMAL_PRIORITY_CLASS;
		case 5:
			return HIGH_PRIORITY_CLASS;
		case 6:
			return REALTIME_PRIORITY_CLASS;
		default:
			throw "Incorrect process priority";
	}
}

int main(int argc, char* argv[])
{
	HANDLE currentProcess = GetCurrentProcess();

	if (argc != 4) {
		throw "Wrong number of parameters\n";
	}

	try {
		HANDLE currentProcess = GetCurrentProcess();

		DWORD affinityMask = atoi(argv[1]);
		DWORD firstProcessPriority = atoi(argv[2]);
		DWORD secondProcessPriority = atoi(argv[3]);
		LPCWSTR filePath = L"C:\\Univer\\OS\\Lab5\\Windows\\OS05_02x\\x64\\Debug\\OS05_02x.exe";

		if (!SetProcessAffinityMask(currentProcess, affinityMask)) {
			throw "SetProcessAffinityMask error";
		}

		STARTUPINFO startupInfoFirst;
		STARTUPINFO startupInfoSecond;

		PROCESS_INFORMATION processInfoFirst;
		PROCESS_INFORMATION processInfoSecond;

		ZeroMemory(&startupInfoFirst, sizeof(STARTUPINFO));
		ZeroMemory(&startupInfoSecond, sizeof(STARTUPINFO));

		ZeroMemory(&processInfoFirst, sizeof(PROCESS_INFORMATION));
		ZeroMemory(&processInfoSecond, sizeof(PROCESS_INFORMATION));

		startupInfoFirst.cb = sizeof(STARTUPINFO);
		startupInfoSecond.cb = sizeof(STARTUPINFO);

		if (!CreateProcess(filePath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | setPriority(firstProcessPriority), NULL, NULL, &startupInfoFirst, &processInfoFirst))
		{
			throw "First process creation error";
		}

		if (!CreateProcess(filePath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | setPriority(secondProcessPriority), NULL, NULL, &startupInfoSecond, &processInfoSecond))
		{
			throw "Second process creation error";
		}

		WaitForSingleObject(processInfoFirst.hProcess, INFINITE);
		WaitForSingleObject(processInfoSecond.hProcess, INFINITE);

		CloseHandle(processInfoFirst.hProcess);
		CloseHandle(processInfoSecond.hProcess);
	}
	catch (char* error)
	{
		cout << "OS05_02: " << error;
	}

	return 0;
}