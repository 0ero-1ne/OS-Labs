#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char c;
	int rowNumber = 0;
	int in = open("./OS09_05.txt", O_RDONLY);
	
	while (read(in,&c,1) == 1)
		if(c == '\n') rowNumber++;

	printf("Number of lines: %d \n", rowNumber == 0 ? 0 : rowNumber + 1);
	return 0;
}