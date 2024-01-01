#include <iostream>
#include <Windows.h>

void sh(HANDLE heap)
{
	PROCESS_HEAP_ENTRY heap_data;
	heap_data.lpData = NULL;
	int size = 0, uncommited = 0, busy = 0;
	while (HeapWalk(heap, &heap_data))
	{
		size += heap_data.cbData;
		heap_data.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE ? uncommited += heap_data.cbData : NULL;
		heap_data.wFlags & PROCESS_HEAP_ENTRY_BUSY ? busy += heap_data.cbData : NULL;
	}
	std::cout << std::dec << "Amount Size = " << size << "\nUncommited = " << uncommited << "\nBusy = " << busy << std::endl;
}

int main()
{
	HANDLE heap = GetProcessHeap();

	std::cout << "BEFORE\n";
	sh(heap);

	int* data = new int[300000];

	std::cout << "\nAFTER\n";
	sh(heap);

	return 0;
}