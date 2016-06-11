#include "myStdlib.h"

int main(void)
{
	char * buffer = malloc(50);
	strcpy(buffer, "Hola, mundo");
	printf("%s\n", buffer);
	free(buffer);
	return 0;
}