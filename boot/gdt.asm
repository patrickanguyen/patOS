gdt_start:

gdt_null:
    dd 0x0 ; 8 byte null descriptor 
    dd 0x0

gdt_code: ; The code segment descriptor
    ; 1st flags: Present 1, Privledge 00, Descriptor type 1
    ; type flags: Code 1, Conforming 0, readable 1, accessed 0
    ; 2nd flags: granularity 1, 32-bit default, 1, 64 0, avl, 0
    dw 0xffff ; Limit (0-15)
    dw 0x0 ; Base 
    db 0x0 ; Base
    db 10011010b ; 1st flag, type flags
    db 11001111b ; 2nd flags, limit
    db 0x0 ; Base

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b ; 2nd flags, limit
    db 0x0 ; Base

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size of gdt
    dd gdt_start ; start address of gdt

CODE_SEG equ gdt_code - gdt_start
    
DATA_SEG equ gdt_data - gdt_start
    