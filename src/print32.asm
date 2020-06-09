[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    mov al, [ebx] 
    mov ah, WHITE_ON_BLACK

    cmp al, 0 ; jmp to done if null character
    je done

    ; Store char and attribute and current char cell
    mov [edx], ax 

    add ebx, 1 ; Increment to next char
    add edx, 2 ; Move to next character cell in video mem.

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret