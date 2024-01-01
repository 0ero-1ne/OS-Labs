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
	HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 1024 * 1024 * 4, 0);
	sh(heap);
	std::cout << std::endl;

	int* m = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 300000 * sizeof(int));
	sh(heap);
	std::cout << std::endl;

	HeapFree(heap, HEAP_NO_SERIALIZE, m);
	sh(heap);

	HeapDestroy(heap);

	return 0;
}