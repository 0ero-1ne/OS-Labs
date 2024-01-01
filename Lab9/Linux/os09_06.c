#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char c;
	int rowNumber = 0, out, num;
	int in = open("./OS09_05.txt", O_RDONLY);
	bool yaBool = false;
	
	if (argc != 2)
	{
		printf("No parameter\n");
		exit(1);
	}

	if (atoi(argv[1]) <= 0) {
		printf("Wrong parameter");
	}

	num = atoi(argv[1]);
	
	if (num % 2 != 0)
		out = open("./OS09_06_1.txt", O_CREAT | O_WRONLY, 0777);
	else
	{
		out = open("./OS09_06_2.txt", O_CREAT | O_WRONLY, 0777);
		yaBool = true;
	}
	
	while (read(in, &c, 1) == 1)
	{
		if (!yaBool)
			write(out, &c, 1);
		if (c == '\n')
			yaBool = !yaBool;
	}

	close(out);
	close(in);

    return 0;
}