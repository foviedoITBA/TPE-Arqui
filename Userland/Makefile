include Makefile.inc

MODULE=console.bin
DATA=data.bin
SOURCES_C=console.c myStdlib.c
SOURCES_ASM=$(wildcard *.asm)
OBJECTS_C=$(SOURCES_C:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS=$(OBJECTS_C) $(OBJECTS_ASM)

all: $(MODULE) $(DATA)

$(MODULE): $(OBJECTS)
	$(LD) -T console.ld $(OBJECTS_C) $(OBJECTS_ASM) -o $(MODULE)

$(DATA):
	echo "100" > data.bin

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o *.bin

.PHONY: all clean
