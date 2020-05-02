all: boot.bin

boot.bin: src/*
	nasm src/boot.asm -f bin -o boot.bin -i src/

run: boot.bin
	qemu-system-x86_64 boot.bin 
