#include "myStdlib.h"

int main(void)
{
	char * buffer = malloc(1024);
	while(1)
	{
		printf("$> ");
		for (int i = 0; i < 1000; i++)
			buffer[i] = '\0';
		scanf(buffer, 1000);
		printf("INVALID COMMAND: %s", buffer);
	}
}