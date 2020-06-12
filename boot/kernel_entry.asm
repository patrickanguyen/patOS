global _start
[bits 32]

_start:
    [extern kernel_main] ; Declare that we will reference external symbol main
    call kernel_main ; Call main in C kernel
    jmp $