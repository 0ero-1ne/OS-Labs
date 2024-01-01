#include <stdio.h>
#include <Windows.h>

int main()
{
	for (int i = 1; i < 1000000; i++)
	{
		printf("Iteration %d\n", i);
		Sleep(1000);
	}

	return 0;
}