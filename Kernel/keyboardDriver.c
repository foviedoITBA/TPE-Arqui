#include "keyboardDriver.h"
#include "videoDriver.h"

#define BUFFER_SIZE 1024
#define TABLE_SIZE 0x3B;
#define NULL_CHAR (char) 0
#define ESC 1
#define BACKSPACE 2
#define TAB 3
#define LEFT_SHIFT 4
#define RIGHT_SHIFT 5
#define CAPS 6


static char keyboard_buffer[BUFFER_SIZE];
static int index = 0;

static char low_ascii[] = {NULL_CHAR, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', NULL_CHAR, BACKSPACE, 
							TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', NULL_CHAR, '+', '\n', NULL_CHAR,
							'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', NULL_CHAR, '{', '}', LEFT_SHIFT, '<', 'z', 'x', 'c',
							'v', 'b', 'n', 'm', ',', '.', '-', RIGHT_SHIFT, NULL_CHAR, NULL_CHAR, ' ', CAPS};
static char high_ascii[] = {NULL_CHAR, ESC, '!', '\"', '#', '$', '%', '&', '/', '(', ')', '=', '?', NULL_CHAR, BACKSPACE,
								TAB, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', NULL_CHAR, '+', '\n', NULL_CHAR,
								'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', NULL_CHAR, '[', ']', LEFT_SHIFT, '>', 'Z', 'X',
								'C', 'V', 'B', 'N', 'M', ';', ':', '_', RIGHT_SHIFT, NULL_CHAR, NULL_CHAR, ' ', CAPS};
static char * active_table = low_ascii;
static int left_shift = 0, right_shift = 0;

void key_handler(uint64_t key_scan_code)
{
	
	print_msg("Keyboard interrupt\n", RED, WHITE);
}