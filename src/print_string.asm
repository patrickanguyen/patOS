print_string:
    pusha

start:
    mov al, [bx]
    cmp al, 0
    je end

    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp start

end:
    popa
    ret

