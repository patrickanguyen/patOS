SRC_DIR = src
FILES = src/boot.asm

all: boot.bin
.PHONY: all

boot.bin: $(FILES)
	nasm $^ -f bin -o $@ -i src/

%.asm:
	echo $@

run: boot.bin
	qemu-system-x86_64 boot.bin

.PHONY: run

clean:
	rm boot.bin
