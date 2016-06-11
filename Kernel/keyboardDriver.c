#include "keyboardDriver.h"
#include "videoDriver.h" /* FOR DEBUGGING ONLY */

#define BUFFER_SIZE 1024
#define TABLE_SIZE 0x3B
#define NULL_CHAR (char) 0
#define ESC 1
#define BACKSPACE 2
#define LEFT_SHIFT 3
#define RIGHT_SHIFT 4
#define CAPS 5


static char keyboard_buffer[BUFFER_SIZE];
static int index = 0;

static char no_shift_no_caps_table[TABLE_SIZE] = {NULL_CHAR, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', NULL_CHAR, BACKSPACE, 
							'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', NULL_CHAR, '+', '\n', NULL_CHAR,
							'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', NULL_CHAR, '{', '}', LEFT_SHIFT, '<', 'z', 'x', 'c',
							'v', 'b', 'n', 'm', ',', '.', '-', RIGHT_SHIFT, NULL_CHAR, NULL_CHAR, ' ', CAPS};
static char shift_no_caps_table[TABLE_SIZE] = {NULL_CHAR, ESC, '!', '\"', '#', '$', '%', '&', '/', '(', ')', '=', '?', NULL_CHAR, BACKSPACE,
								'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', NULL_CHAR, '*', '\n', NULL_CHAR,
								'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', NULL_CHAR, '[', ']', LEFT_SHIFT, '>', 'Z', 'X',
								'C', 'V', 'B', 'N', 'M', ';', ':', '_', RIGHT_SHIFT, NULL_CHAR, NULL_CHAR, ' ', CAPS};
static char no_shift_caps_table[TABLE_SIZE] = {NULL_CHAR, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', NULL_CHAR, BACKSPACE,
								'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', NULL_CHAR, '+', '\n', NULL_CHAR,
								'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', NULL_CHAR, '{', '}', LEFT_SHIFT, '<', 'Z', 'X',
								'C', 'V', 'B', 'N', 'M', ',', '.', '-', RIGHT_SHIFT, NULL_CHAR, NULL_CHAR, ' ', CAPS};
static char shift_caps_table[TABLE_SIZE] = {NULL_CHAR, ESC, '!', '\"', '#', '$', '%', '&', '/', '(', ')', '=', '?', NULL_CHAR, BACKSPACE, 
							'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', NULL_CHAR, '*', '\n', NULL_CHAR,
							'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', NULL_CHAR, '[', ']', LEFT_SHIFT, '>', 'z', 'x', 'c',
							'v', 'b', 'n', 'm', ';', ':', '_', RIGHT_SHIFT, NULL_CHAR, NULL_CHAR, ' ', CAPS};


static char * active_table = no_shift_no_caps_table;
static int left_shift = 0, right_shift = 0, caps = 0;

void key_handler(uint64_t key_scan_code)
{
	uint64_t key_index = key_scan_code & 0x7F;
	int is_break_code = key_scan_code & 0x80;
	if (key_index >= TABLE_SIZE || active_table[key_index] == NULL_CHAR)
		return;
	switch(active_table[key_index])
	{
		case ESC:
			if (!is_break_code)	
			{	
				keyboard_buffer[index] = '\0';
				print_msg(keyboard_buffer, BLUE, GREEN);
				index = 0;
			}
			break;
		case BACKSPACE:
			if (index > 0 && !is_break_code)
				index--;
			break;
		case LEFT_SHIFT:
			left_shift = !is_break_code;
			break;
		case RIGHT_SHIFT:
			right_shift = !is_break_code;
			break;
		case CAPS:
			if (!is_break_code)
				caps = 1 - caps;
			break;
		default:
			if (!is_break_code)
				keyboard_buffer[index++] = active_table[key_index];
			break;
	}
	
	if ((left_shift || right_shift) && caps)
		active_table = shift_caps_table;
	else if (!(left_shift || right_shift) && caps)
		active_table = no_shift_caps_table;
	else if (left_shift || right_shift)
		active_table = shift_no_caps_table;
	else
		active_table = no_shift_no_caps_table;
}