[bits 32]
[extern main] ; Declare that we will reference external symbol main

call main ; Call main in C kernel
jmp $