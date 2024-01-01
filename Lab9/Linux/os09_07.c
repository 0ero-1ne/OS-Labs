#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
	int in;
	long pos, offs;               
	char buffer[10];
	
	in = open("./OS09_05.txt",O_RDONLY);
	offs = 0L;
	pos = lseek(in, offs, SEEK_SET);
	printf("Current position = %ld\n", pos);
    read(in, buffer, 10);
	printf("Read chars: %s\n", buffer);
	
	offs = 10L;
	pos = lseek(in, offs, SEEK_CUR);
	printf("Current position = %ld\n", pos);
	read(in, buffer, 10);
	printf("10 chars read: %s\n", buffer);
	
	offs = 20L;
	pos = lseek(in, offs, SEEK_CUR);
	printf("Current position = %ld\n", pos);
    read(in, buffer, 10);
	printf("Read chars: %s\n", buffer);

    offs = 30L;
    pos = lseek(in, offs, SEEK_END);
	printf("Current position = %ld\n", pos);

	close(in);
	return 0;
}