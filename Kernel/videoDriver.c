#include "videoDriver.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define BLACK_ON_BLACK 0
#define FOREGROUND_INTENSITY_MASK 0x8
#define BACKGROUND_INTENSITY_MASK 0x80
#define IS_COLOR(x) (x >= 0 && x < 8 ? 1 : 0)
#define TAB_SPACE 5

static char *video = (char *) 0xB8000;
static int position = 0;

void clear_screen()
{
	int i, j;
	for (i = 0; i < SCREEN_HEIGHT; i++)
		for (j = 0; j < SCREEN_WIDTH; j++)
			*(video + 2*i*SCREEN_HEIGHT + 2*j) = BLACK_ON_BLACK;
	reset_position();
}

void reset_position()
{
	position = 0;
}

void print_msg(char * msg, int foreground_color, int background_color)
{
	
	unsigned char attribute;
	int i;
	if(!IS_COLOR(foreground_color) || !IS_COLOR(background_color))
		return;
	attribute = foreground_color | (background_color << 4);
	attribute = attribute | FOREGROUND_INTENSITY_MASK;
	attribute = attribute | BACKGROUND_INTENSITY_MASK;
	
	for (i = 0; msg[i] != '\0'; i++)
	{
		if (msg[i] == '\n')
		{
			int newPosition = 0;
			while(newPosition <= position)
				newPosition += SCREEN_WIDTH;
			position = newPosition;
		}
		else if (msg[i] == '\t')
		{
			int j;
			for (j = 0; j < TAB_SPACE; j++)
			{
				video[2*position] = ' ';
				video[2*position+1] = attribute;
				position++;
			}
		}	
		else
		{
			video[2*position] = msg[i];
			video[2*position+1] = attribute;
			position++;
		}
	}
}

