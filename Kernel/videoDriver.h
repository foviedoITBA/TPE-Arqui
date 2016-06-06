#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

enum {BLACK = 0, BLUE, GREEN, LIGHTBLUE, RED, PINK, ORANGE, WHITE};

void clear_screen();
void print_msg(char* msg, int foreground_color, int background_color);
void reset_position();

#endif