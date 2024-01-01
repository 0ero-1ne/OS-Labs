#include <iostream>
#include <Windows.h>

using namespace std;

int countProcessors(ULONG_PTR mask) {
	int count = 0;

	while (mask) {
		count += mask & 1;
		mask >>= 1;
	}

	return count;
}

int main()
{
	DWORD processId = GetCurrentProcessId();
	DWORD threadId = GetCurrentThreadId();

	cout << "Process ID: " << processId << endl;
	cout << "Thread ID: " << threadId << endl;
	
	DWORD processPriority = GetPriorityClass(GetCurrentProcess());
	DWORD threadPriority = GetThreadPriority(GetCurrentThread());

	switch (processPriority)
	{
		cout << "Process priority: ";
		case IDLE_PRIORITY_CLASS:
			cout << "IDLE_PRIORITY_CLASS\n";
			break;
		case BELOW_NORMAL_PRIORITY_CLASS:
			cout << "BELOW_NORMAL_PRIORITY_CLASS\n";
			break;
		case NORMAL_PRIORITY_CLASS:
			cout << "NORMAL_PRIORITY_CLASS\n";
			break;
		case ABOVE_NORMAL_PRIORITY_CLASS:
			cout << "ABOVE_NORMAL_PRIORITY_CLASS\n";
			break;
		case HIGH_PRIORITY_CLASS:
			cout << "HIGH_PRIORITY_CLASS\n";
			break;
		case REALTIME_PRIORITY_CLASS:
			cout << "REALTIME_PRIORITY_CLASS\n";
			break;
		default:
			cout << "UNKNOWN_PRIORITY\n";
			break;
	}

	switch (threadPriority)
	{
		cout << "Thread priority: ";
		case THREAD_PRIORITY_LOWEST:
			cout << "THREAD_PRIORITY_LOWEST\n";
			break;
		case THREAD_PRIORITY_BELOW_NORMAL:
			cout << "THREAD_PRIORITY_BELOW_NORMAL\n";
			break;
		case THREAD_PRIORITY_NORMAL:
			cout << "THREAD_PRIORITY_NORMAL\n";
			break;
		case THREAD_PRIORITY_ABOVE_NORMAL:
			cout << "THREAD_PRIORITY_ABOVE_NORMAL\n";
			break;
		case THREAD_PRIORITY_HIGHEST:
			cout << "THREAD_PRIORITY_HIGHEST\n";
			break;
		case THREAD_PRIORITY_IDLE:
			cout << "THREAD_PRIORITY_IDLE\n";
			break;
		default:
			cout << "UNKNOWN_PRIORITY\n";
			break;
	}

	DWORD_PTR lpProcessAffinityMask = NULL;
	DWORD_PTR lpSystemAffinityMask = NULL;

	char affinityMask[64];

	if (!GetProcessAffinityMask(GetCurrentProcess(), &lpProcessAffinityMask, &lpSystemAffinityMask))
		throw "GetProcessAffinityMask: Error\n";

	_itoa_s(lpProcessAffinityMask, affinityMask, 2);
	cout << "Process afinity mask: " << affinityMask << endl;
	
	DWORD_PTR threadProcessor = SetThreadIdealProcessor(GetCurrentThread(), MAXIMUM_PROCESSORS);

	cout << "Processors number of process: " << countProcessors(lpProcessAffinityMask) << endl;
	cout << "Current thread processor: " << threadProcessor << endl;

	return 0;
}