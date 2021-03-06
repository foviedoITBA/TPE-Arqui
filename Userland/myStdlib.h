#ifndef MY_STDLIB_H
#define MY_STDLIB_H

int strlen(char s[]);
void strcpy(char target[], const char source[]);
int strcmp(const char * str1, const char * str2);
void printf(const char * format, ...);
void putchar(char c);
void * malloc(int bytes);
void free(void * p);
void scanf(char * buffer, int bytes);
void fractal();

#endif