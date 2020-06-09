[org 0x7c00]
    mov [BOOT_DRIVE], dl ; Store boot drive

    mov bp, 0x8000 ; Set stack out of the way
    mov sp, bp

    mov bx, 0x9000 ; Load 5 sectors from boot disk
    mov dh, 2
    mov dl, [BOOT_DRIVE] 
    call disk_load

    mov dx, [0x9000] ; Print first loaded word, which should 0xdada
    call print_hex

    mov dx, [0x9000 + 512] ; Print first word from second loaded sector
    call print_hex ; should be 0xface

    jmp $

%include "print_string.asm"
%include "print_hex.asm"
%include "disk_load.asm"

BOOT_DRIVE:
    db 0

; Bootsector padding
times 510-($-$$) db 0
dw 0xaa55

; Add sectors to our code to show that we actually
; loaded two sectors from disk we booted from
times 256 dw 0xdada
times 256 dw 0xface