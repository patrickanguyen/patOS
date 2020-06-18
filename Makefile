# Change this to the location of your cross-complier/linker
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld

# Directories of C source files
C_DIR = cpu drivers kernel pat_libc

C_SOURCES = $(shell find $(C_DIR) -type f -name '*.c')
ASM_SOURCES = boot/kernel_entry.asm cpu/interrupt.asm 
HEADERS = $(C_SOURCES:.c=.h)
C_OBJECTS = $(C_SOURCES:.c=.o)
ASM_OBJECTS = $(ASM_SOURCES:.asm=.o)

BIN_NAME = patOS-image.bin

CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -ffreestanding

.PHONY: all run clean

all: $(BIN_NAME)

run: $(BIN_NAME)
	qemu-system-i386 -drive format=raw,file=$<,index=0,if=floppy
 
$(BIN_NAME): boot/bootsect.bin kernel.bin
	cat $^ > $@

kernel.bin: $(ASM_OBJECTS) $(C_OBJECTS) 
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

boot/bootsect.bin: boot/bootsect.asm
	nasm $< -f bin -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

clean:
	rm -rf $(BIN_NAME) kernel.bin boot/bootsect.bin
	rm -rf $(C_OBJECTS) $(ASM_OBJECTS) 