#include "myStdlib.h"

#define MAX_COMMAND_SIZE 100
#define MAX_ARGUMENT_SIZE 100

void invalid_command_msg(char * buffer);

int main(void)
{
	char * buffer = malloc(1024);
	char * command = malloc(MAX_COMMAND_SIZE);
	char * argument = malloc(MAX_ARGUMENT_SIZE);
	for (int i = 0; i < 1000; i++)
		buffer[i] = '\0';
	while(1)
	{
		printf("$> ");
		for (int i = 0; buffer[i] != '\0' && i < 1000; i++)
			buffer[i] = '\0';
		scanf(buffer, 1000);
		if (buffer[0] == '\n')
			continue;
		int j;
		for (j = 0; buffer[j] != ' ' && buffer[j] != '\n' && j < MAX_COMMAND_SIZE-1; j++)
			command[j] = buffer[j];
		command[j] = '\0';
		if (buffer[j] == '\n')
		{
			if (strcmp(command, "help") == 0)
				printf("The available commands are:\n\thelp\n\techo <message>\n\tfractal\n");
			else if (strcmp(command, "fractal") == 0)
				fractal();
			else
				invalid_command_msg(buffer);
		}
		else if (buffer[j] == ' ')
		{
			int k = 0;
			for (j++; buffer[j] != '\n' && k < MAX_ARGUMENT_SIZE-1; j++, k++)
				argument[k] = buffer[j];
			argument[k] = '\0';
			if (strcmp(command, "echo") == 0)
				printf("%s\n", argument);
			else
				invalid_command_msg(buffer);
		}
		else 
			invalid_command_msg(buffer);
	}
	free(buffer);
	free(command);
	free(argument);
}

void invalid_command_msg(char * buffer)
{
	printf("Invalid command: %s", buffer);
}