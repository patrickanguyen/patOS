[org 0x7c00]

mov bx, HELLO_MSG
call print_string

mov bx, GOODBYE_MSG
call print_string

mov dx, 0x1fb5
call print_hex

call print_hex

jmp $

%include "print_string.asm"
%include "print_hex.asm"

HELLO_MSG:
    db 'Hello World', 0xd, 0xa, 0

GOODBYE_MSG:
    db 'Goodbye', 0xd, 0xa, 0

times 510-($-$$) db 0
dw 0xaa55
