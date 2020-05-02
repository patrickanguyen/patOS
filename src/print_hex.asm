print_hex:
; Input dx = hex integer
; Print hex integer to screen
    pusha
    mov cx, 0 ; int i = 0

hex_loop:   
    cmp cx, 4
    je end_hex_loop

    ; Convert digit to ASCII character
    mov ax, dx
    and ax, 0x000f
    add ax, 0x30
    
    ; If digit is > 9, add 
    cmp ax, 0x39
    jle end_ascii_convert 
    add ax, 7

end_ascii_convert:
    mov bx, HEX_OUT + 5
    sub bx, cx

    mov [bx], al
    shr dx, 4

    add cx, 1
    jmp hex_loop
end_hex_loop:
     
    mov bx, HEX_OUT
    call print_string
    popa
    ret 

HEX_OUT:
    db '0x0000', 0xd, 0xa, 0
