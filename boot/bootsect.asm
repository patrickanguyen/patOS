[org 0x7c00]
KERNEL_OFFSET equ 0x1000

    mov [BOOT_DRIVE], dl

    mov bp, 0x9000 ; Set stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print_string

    call load_kernel ; Load kernel

    call switch_to_pm ; Switch to protected mode

    jmp $

%include "boot/print_string.asm"
%include "boot/disk_load.asm"
%include "boot/gdt.asm"
%include "boot/print_pm.asm"
%include "boot/switch_to_pm.asm"

[bits 16]

load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET ; Load first 15 sectors from boot disk
    mov dh, 15 ; to address KERNEL_OFFSET
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

[bits 32]
; Finished switching to protected mode
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    call KERNEL_OFFSET ; Jump to address of loaded kernel code
    jmp $


; Global variables
BOOT_DRIVE:
    db 0x0

MSG_REAL_MODE:
    db "Started in 16-bit real mode", 0xa, 0xd, 0

MSG_PROT_MODE:
    db "Sucessfully landed in 32-bit protected Mode", 0

MSG_LOAD_KERNEL:
    db "Loading kernel into memory", 0xa, 0xd, 0

; Bootsector padding
times 510-($-$$) db 0
dw 0xaa55
