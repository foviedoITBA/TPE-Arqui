#include "vga.h"
#include "bga.h"
#include "IO_ASM.h"
#include <stdint.h>

#define X_RESOLUTION 1024
#define Y_RESOLUTION 768
#define BPP 32
#define BYTES_IN_KB 1024
#define BITS_IN_BYTE 8

#define BANKS ((X_RESOLUTION*Y_RESOLUTION*BPP/BITS_IN_BYTE)/(VBE_DISPI_BANK_SIZE_KB*BYTES_IN_KB))

extern void * get_data_address();

static void start_video_mode();
static void write_register(uint16_t index, uint16_t data);
static void plot_point(uint32_t x, uint32_t y, uint32_t color);
static void plot_fractal();
static int get_fractal_data();

typedef enum {FALSE, TRUE} BOOL;

typedef struct
{
	float r;
	float i;
} complex;

void print_fractal()
{
	start_video_mode();
	plot_fractal(get_fractal_data());
	while(1);
}

static void start_video_mode()
{
	write_register(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
	write_register(VBE_DISPI_INDEX_XRES, X_RESOLUTION);
	write_register(VBE_DISPI_INDEX_YRES, Y_RESOLUTION);
	write_register(VBE_DISPI_INDEX_BPP, BPP);
	write_register(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED);
}

static void write_register(uint16_t index, uint16_t data)
{
    _out_16(VBE_DISPI_IOPORT_INDEX, index);
    _out_16(VBE_DISPI_IOPORT_DATA, data);
}

static void plot_point(uint32_t x, uint32_t y, uint32_t color)
{
	static int last_bank = 0;
	if (last_bank != y/(Y_RESOLUTION/BANKS))
	{
		last_bank = y/(Y_RESOLUTION/BANKS);
		write_register(VBE_DISPI_INDEX_BANK, last_bank);
	}
	*(((uint32_t *) 0xA0000) + x + y%(Y_RESOLUTION/BANKS)*X_RESOLUTION) = color;
}

/* Mandelbrot set */
static void plot_fractal(int max_iterations)
{
	complex c, z;
	for (float y = -2; y <=2; y += 4.0/Y_RESOLUTION)
		for (float x = -2; x <=2; x += 4.0/X_RESOLUTION)
		{
			int iterations;
			BOOL should_plot = TRUE;
			c.r = x;
			c.i = y;
			z.r = z.i = 0;
			for (iterations = 0; z.r*z.r + z.i*z.i < 4 && iterations < max_iterations; iterations++)
			{
				complex temp = z;
				temp.r = z.r*z.r - z.i*z.i + c.r;
				temp.i = 2*z.r*z.i + c.i;
				z = temp;
				if (z.r*z.r + z.i*z.i >= 4)
					should_plot = FALSE;
			}
			if (should_plot)
			{	
				uint32_t color = (uint32_t)((x*x+y*y)*X_RESOLUTION*Y_RESOLUTION/4) & 0x00FFFFFF;
				plot_point(X_RESOLUTION*(1+x/2)/2, Y_RESOLUTION*(1+y/2)/2, color);
			}
		}
}

static int get_fractal_data()
{
	char * data = (char *) get_data_address();
	int num = 0, i = 0;
	while('0' <= data[i] && data[i] <= '9')
		num = 10*num + (data[i++] - '0');
	return num;
}