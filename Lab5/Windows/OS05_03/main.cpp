#include <iostream>
#include <Windows.h>

using namespace std;

DWORD getProcessPriority(DWORD processPriority)
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

DWORD getThreadPriority(DWORD threadPriority)
{
	switch (threadPriority) {
	case 1:
		return THREAD_PRIORITY_IDLE;
	case 2:
		return THREAD_PRIORITY_LOWEST;
	case 3:
		return THREAD_PRIORITY_BELOW_NORMAL;
	case 4:
		return THREAD_PRIORITY_NORMAL;
	case 5:
		return THREAD_PRIORITY_ABOVE_NORMAL;
	case 6:
		return THREAD_PRIORITY_HIGHEST;
	case 7:
		return REALTIME_PRIORITY_CLASS;
	default:
		throw "Incorrect thread priority";
	}
}

void printProcessPriority(DWORD processPriority)
{
	switch (processPriority)
	{
		case IDLE_PRIORITY_CLASS:
			printf("Process priority: --- IDLE_PRIORITY_CLASS ---\n");
			break;
		case BELOW_NORMAL_PRIORITY_CLASS:
			printf("Process priority: --- BELOW_NORMAL_PRIORITY_CLASS ---\n");
			break;
		case NORMAL_PRIORITY_CLASS:
			printf("Process priority: --- NORMAL_PRIORITY_CLASS ---\n");
			break;
		case ABOVE_NORMAL_PRIORITY_CLASS:
			printf("Process priority: --- ABOVE_NORMAL_PRIORITY_CLASS ---\n");
			break;
		case HIGH_PRIORITY_CLASS:
			printf("Process priority: --- HIGH_PRIORITY_CLASS ---\n");
			break;
		case REALTIME_PRIORITY_CLASS:
			printf("Process priority: --- REALTIME_PRIORITY_CLASS ---\n");
			break;
		default:
			printf("Process priority: --- UNKNOWN_PRIORITY ---\n");
			break;
	}
}

void printThreadPriority(DWORD threadPriority)
{
	switch (threadPriority)
	{
		case THREAD_PRIORITY_LOWEST:
			printf("Thread priority: --- THREAD_PRIORITY_LOWEST ---\n");
			break;
		case THREAD_PRIORITY_BELOW_NORMAL:
			printf("Thread priority: --- THREAD_PRIORITY_BELOW_NORMAL ---\n");
			break;
		case THREAD_PRIORITY_NORMAL:
			printf("Thread priority: --- THREAD_PRIORITY_NORMAL ---\n");
			break;
		case THREAD_PRIORITY_ABOVE_NORMAL:
			printf("Thread priority: --- THREAD_PRIORITY_ABOVE_NORMAL ---\n");
			break;
		case THREAD_PRIORITY_HIGHEST:
			printf("Thread priority: --- THREAD_PRIORITY_HIGHEST ---\n");
			break;
		case THREAD_PRIORITY_IDLE:
			printf("Thread priority: --- THREAD_PRIORITY_IDLE ---\n");
			break;
		default:
			printf("Thread priority: --- UNKNOWN_PRIORITY ---\n");
			break;
	}
}

DWORD WINAPI TA()
{
	for (int i = 1; i < 1000000; i++) {
		if (i % 1000 == 0 || i == 1) {
			printf("Iteration number: --- %d ---\n", i);
			printf("PID: --- %d ---\n", GetCurrentProcessId());
			printf("TID: --- %d ---\n", GetCurrentThreadId());

			DWORD processPriority = GetPriorityClass(GetCurrentProcess());
			DWORD threadPriority = GetThreadPriority(GetCurrentThread());

			printProcessPriority(processPriority);
			printThreadPriority(threadPriority);

			SYSTEM_INFO systemInfo;
			GetSystemInfo(&systemInfo);

			DWORD_PTR threadProcessor;
			threadProcessor = SetThreadIdealProcessor(GetCurrentThread(), MAXIMUM_PROCESSORS);

			printf("Current thread processor: --- %d ---\n", threadProcessor);
			printf("-----------------------------------------------------------------\n");
			Sleep(200);
		}
	}
	printf("Thread %d completed!\n", GetCurrentThreadId());

	return 0;
}

int main(int argc, char* argv[])
{
	HANDLE currentProcess = GetCurrentProcess();

	if (argc != 5) {
		throw "Wrong number of parameters\n";
	}

	try {
		HANDLE currentProcess = GetCurrentProcess();

		DWORD affinityMask = atoi(argv[1]);
		DWORD processPriority = atoi(argv[2]);
		DWORD firstThreadPriority = atoi(argv[3]);
		DWORD secondThreadPriority = atoi(argv[4]);

		if (!SetProcessAffinityMask(currentProcess, affinityMask)) {
			throw "SetProcessAffinityMask error";
		}

		if (!SetPriorityClass(currentProcess, getProcessPriority(processPriority))) {
			throw "SerPriorityClass error";
		}

		HANDLE firstThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, 0, NULL);
		HANDLE secondThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, 0, NULL);

		SetThreadPriority(firstThread, getThreadPriority(firstThreadPriority));
		SetThreadPriority(secondThread, getThreadPriority(secondThreadPriority));

		WaitForSingleObject(firstThread, INFINITE);
		WaitForSingleObject(secondThread, INFINITE);

		CloseHandle(firstThread);
		CloseHandle(secondThread);
	}
	catch (char* error)
	{
		cout << "OS05_02: " << error;
	}

	return 0;
}