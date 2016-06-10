include Makefile.inc

MODULE=console.bin
SOURCES_C=console.c
SOURCES_ASM=consoleASM.asm
OBJECTS_C=$(SOURCES_C:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS=$(OBJECTS_C) $(OBJECTS_ASM)

all: $(MODULE)

$(MODULE): $(OBJECTS)
	$(LD) -T console.ld $(OBJECTS_C) $(OBJECTS_ASM) -o $(MODULE)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o

.PHONY: all clean
