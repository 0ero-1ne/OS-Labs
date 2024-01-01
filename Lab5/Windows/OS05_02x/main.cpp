#include <iostream>
#include <Windows.h>

using namespace std;

void printProcessPriority(DWORD processPriority)
{
	switch (processPriority)
	{
		cout << "Process priority: ";
		case IDLE_PRIORITY_CLASS:
			cout << "IDLE_PRIORITY_CLASS ---\n";
			break;
		case BELOW_NORMAL_PRIORITY_CLASS:
			cout << "BELOW_NORMAL_PRIORITY_CLASS ---\n";
			break;
		case NORMAL_PRIORITY_CLASS:
			cout << "NORMAL_PRIORITY_CLASS ---\n";
			break;
		case ABOVE_NORMAL_PRIORITY_CLASS:
			cout << "ABOVE_NORMAL_PRIORITY_CLASS ---\n";
			break;
		case HIGH_PRIORITY_CLASS:
			cout << "HIGH_PRIORITY_CLASS ---\n";
			break;
		case REALTIME_PRIORITY_CLASS:
			cout << "REALTIME_PRIORITY_CLASS ---\n";
			break;
		default:
			cout << "UNKNOWN_PRIORITY ---\n";
			break;
	}
}

void printThreadPriority(DWORD threadPriority)
{
	switch (threadPriority)
	{
		cout << "Thread priority: ";
		case THREAD_PRIORITY_LOWEST:
			cout << "THREAD_PRIORITY_LOWEST ---\n";
			break;
		case THREAD_PRIORITY_BELOW_NORMAL:
			cout << "THREAD_PRIORITY_BELOW_NORMAL ---\n";
			break;
		case THREAD_PRIORITY_NORMAL:
			cout << "THREAD_PRIORITY_NORMAL ---\n";
			break;
		case THREAD_PRIORITY_ABOVE_NORMAL:
			cout << "THREAD_PRIORITY_ABOVE_NORMAL ---\n";
			break;
		case THREAD_PRIORITY_HIGHEST:
			cout << "THREAD_PRIORITY_HIGHEST ---\n";
			break;
		case THREAD_PRIORITY_IDLE:
			cout << "THREAD_PRIORITY_IDLE ---\n";
			break;
		default:
			cout << "UNKNOWN_PRIORITY ---\n";
			break;
	}
}

int main()
{
	for (int i = 1; i < 1000000; i++) {
		if (i % 1000 == 0 || i == 1) {
			cout << "Iteration number: --- " << i << " ---" << endl;
			cout << "PID: --- " << GetCurrentProcessId() << " ---" << endl;
			cout << "TID: --- " << GetCurrentThreadId() << " ---" << endl;

			DWORD processPriority = GetPriorityClass(GetCurrentProcess());
			DWORD threadPriority = GetThreadPriority(GetCurrentThread());

			cout << "Process priority: --- ";
			printProcessPriority(processPriority);
			cout << "Thread priority: --- ";
			printThreadPriority(threadPriority);

			SYSTEM_INFO systemInfo;
			GetSystemInfo(&systemInfo);

			DWORD_PTR threadProcessor;
			threadProcessor = SetThreadIdealProcessor(GetCurrentThread(), MAXIMUM_PROCESSORS);

			cout << "Current thread processor: --- " << threadProcessor << " ---" << endl;
			cout << "-----------------------------------------------------------------\n";
			Sleep(200);
		}
	}

	return 0;
}