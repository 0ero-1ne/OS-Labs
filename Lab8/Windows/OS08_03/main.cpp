#include <stdio.h>
#include <Windows.h>

int main()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	LPVOID xmemaddr = VirtualAlloc(NULL, 256 * si.dwPageSize, MEM_COMMIT, PAGE_READWRITE);
	int* data = (int*)xmemaddr;
	for (int i = 0; i < 256 * si.dwPageSize / sizeof(int); i++)
	{
		data[i] = i;
	}

	const int targetPage = 194;
	const int offset = 3820;

	int* value = data + (targetPage * si.dwPageSize + offset) / sizeof(int);
	printf("Value: %d\n", *value);
	printf("Address: %p\n", value);

	if (!VirtualFree(xmemaddr, NULL, MEM_RELEASE))
		printf("VirtualFree Error\n");

	return 0;
}

/*
	�������: �������
	� - C2
	� - EE
	� - EB

	�������� C2 = 194
	�������� (���� � ��������� �����) EEE = 3822

	194 * 4096 + 3820 = 798444 (C2EEC) / 4 = 199611 (30BBB)
*/