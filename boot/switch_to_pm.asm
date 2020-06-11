[bits 16]

switch_to_pm:
    cli ; Switch of interrupts until we set up protected mode
    
    lgdt [gdt_descriptor]

    mov eax, cr0 ; Set first bit of CR0, a control register
    or eax, 0x1
    mov cr0, eax 

    jmp CODE_SEG:init_pm ; Make a far jump to 32-bit code.

[bits 32]
; Initalize registers and the stack once in PM
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; Update our stack position so it is right position
    mov esp, ebp

    call BEGIN_PM