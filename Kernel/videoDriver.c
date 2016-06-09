#include "videoDriver.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24 /* Last row reserver for clock */
#define BLACK_ON_BLACK 0
#define WHITE_ON_BLACK 7
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

void print_time(int sec, int min, int hrs)
{
	char hrsH, hrsL, minH, minL, secH, secL;
	hrsL = (char) (hrs & 0xF) + '0';
	hrsH = ((char) ((hrs >> 4) & 0x7)) + '0';
	minL = (char) (min & 0xF) + '0';
	minH = ((char) ((min >> 4) & 0x7)) + '0';
	secL = (char) (sec & 0xF) + '0';
	secH = ((char) ((sec >> 4) & 0x7)) + '0';
	
	char currentTime[9];
	currentTime[0] = hrsH;
	currentTime[1] = hrsL;
	currentTime[2] = ':';
	currentTime[3] = minH;
	currentTime[4] = minL;
	currentTime[5] = ':';
	currentTime[6] = secH;
	currentTime[7] = secL;
	currentTime[8] = '\0';

	int i;
	for (int i = 0; currentTime[i] != '\0'; i++)
	{
		*(video + 2 * SCREEN_HEIGHT * SCREEN_WIDTH + 2*i) = currentTime[i];
		*(video + 2 * SCREEN_HEIGHT * SCREEN_WIDTH + 2*i + 1) = WHITE | (BLACK << 4) | FOREGROUND_INTENSITY_MASK | BACKGROUND_INTENSITY_MASK;
	}

//	print_msg(currentTime, WHITE, BLACK);
//	print_msg("\n", WHITE, BLACK);
}
