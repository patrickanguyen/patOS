# patOS

<b>patOS</b> is a hobbyist, educational, 32-bit operating system, implemented in <b>C99</b> and <b>x86 Assembly</b>.

![picture](/img/patOS_shell.gif)

## Building and Running from Source
At the moment, <b>patOS</b> is built using a <b>GCC cross-complier</b> as described at [OSDev.org GCC Cross-Complier](https://wiki.osdev.org/GCC_Cross-Compiler) 
page. After creating a <b>GCC cross-complier</b>, change the path for the complier and linker in the Makefile, then use `make` to build all the files.

After building all the files, you can use then `make run` to emulate <b>patOS</b> by using <b>QEMU</b>, a generic and open source machine emulator and virtualizer.

If ever needed, all the object files can be cleaned up using the `make clean` command.

## Goals
- [X] Boot loader
- [X] GDT
- [X] 32-bit Protected Mode
- [X] VGA Driver
- [X] ISR
- [X] CPU Timer
- [X] Keyboard Driver
- [X] Basic Shell
- [ ] Dynamic Memory
- [ ] File System
- [ ] User Mode
- [ ] Multi-tasking

## Helpful Resources
- [OSDev Wiki](https://wiki.osdev.org/Main_Page)
- [Writing a Simple Operating System - from Scratch by Dr. Nicholas Blundell](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
- [JamesM's Kernel Development Tutorial](http://jamesmolloy.co.uk/tutorial_html/)
- [Operating Systems from 0 to 1](https://github.com/tuhdo/os01)
- Operating System Concepts, A. Silberschatz, P.B. Galvin and G. Gagne
- Computer Systems: A Programmer's Perspective, Bryant and O’Hallaron


## License
This repository is licensed under the [MIT License ](https://choosealicense.com/licenses/mit/)
