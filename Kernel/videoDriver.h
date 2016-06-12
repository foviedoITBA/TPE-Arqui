#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>

enum {BLACK = 0, BLUE, GREEN, LIGHTBLUE, RED, PINK, ORANGE, WHITE};

void clear_screen();
void print_msg(char* msg, int foreground_color, int background_color);
void reset_position();
void print_time(int sec, int min, int hrs);
void video_write(char * buffer, uint64_t bytes);
void video_remove_char();

#endif