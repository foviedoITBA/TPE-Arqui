#include "myStdlib.h"
#include <stdarg.h>

#define PRINT_BUFFER_SIZE 1024
#define BACKSPACE 8

extern void * _malloc(int bytes);
extern void _free(void * p);
extern void _write(char * buffer, int size);
extern void _read(volatile char * key_holder, int bytes);
extern void _remove_char();
extern void _fractal();

int strlen(char s[])
{
	int i;
	for (i = 0; s[i] != '\0'; i++);
	return i;
}

void strcpy(char target[], const char source[])
{
	int i = 0;
	for (i = 0; source[i] != '\0'; i++)
		target[i] = source[i];
	target[i] = '\0';
}

int strcmp(const char * str1, const char * str2)
{
	int i;
	for (i = 0; str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0'; i++);
	return (str2[i] - str1[i]);
}
 
/* AS FROM THE K&R2 BOOK */
/* reverse:  reverse string s in place */
static void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* AS FROM THE K&R2 BOOK */
/* itoa:  convert n to characters in s */
static void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* ADAPTION FROM anizzomc's kprintf */ 
void printf(const char *format, ...)
{
	va_list arg_list;
	va_start(arg_list, format);
	int c;
	char num_buf[20];
	char print_buf[PRINT_BUFFER_SIZE];
	int index = 0;
	
	while ((c = *format++) != 0 && index < PRINT_BUFFER_SIZE-1)
	{
		if (c != '%')
			print_buf[index++] = c;
		else
		{
			char *p;
			c = *format++;
			switch (c)
			{
				case 'd':
					itoa((int) va_arg(arg_list, int), num_buf);
					p = num_buf;
					goto string;
					break;

				case 's':
					p = va_arg(arg_list, char*);
					if (! p)
				    p = "(null)";

				string:
					while (*p)
					{	
						print_buf[index++] = *p++;
						if (index == PRINT_BUFFER_SIZE)
							break;
					}
					break;

				default:
					print_buf[index++] = (char) va_arg(arg_list, int);
					if (index == PRINT_BUFFER_SIZE)
							break;
					break;
			}
		}
	}
	print_buf[1023] = '\0';
	_write(print_buf, index);
}

void putchar(char c)
{
	char buf[] = {c, '\0'};
	_write(buf, sizeof buf);
	return;
}

static void read(char * buffer, int bytes)
{
	int index = 0;
	volatile char key_holder = '\0';
	_read(&key_holder, bytes);
	while(index < bytes)
	{
		if (key_holder == '\0')
			continue;
		else if (key_holder == BACKSPACE)
		{
			if (index > 0)
			{
				buffer[--index] = '\0';
				_remove_char();			
			}
		}
		else
		{
			buffer[index++] = key_holder;
			putchar(key_holder);
		}
		if (key_holder == '\n')
			break;
		key_holder = '\0';
	}
}

/* No es el scanf standard de C */
void scanf(char * buffer, int bytes)
{
	read(buffer, bytes);
}

void * malloc(int bytes)
{
	return _malloc(bytes);
}

void free(void * p)
{
	_free(p);
}

void fractal()
{
	_fractal();
}