#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"

void isr_install() 
{
    idt_set_gate(0, (u32_t)isr0);
    idt_set_gate(1, (u32_t)isr1);
    idt_set_gate(2, (u32_t)isr2);
    idt_set_gate(3, (u32_t)isr3);
    idt_set_gate(4, (u32_t)isr4);
    idt_set_gate(5, (u32_t)isr5);
    idt_set_gate(6, (u32_t)isr6);
    idt_set_gate(7, (u32_t)isr7);
    idt_set_gate(8, (u32_t)isr8);
    idt_set_gate(9, (u32_t)isr9);
    idt_set_gate(10, (u32_t)isr10);
    idt_set_gate(11, (u32_t)isr11);
    idt_set_gate(12, (u32_t)isr12);
    idt_set_gate(13, (u32_t)isr13);
    idt_set_gate(14, (u32_t)isr14);
    idt_set_gate(15, (u32_t)isr15);
    idt_set_gate(16, (u32_t)isr16);
    idt_set_gate(17, (u32_t)isr17);
    idt_set_gate(18, (u32_t)isr18);
    idt_set_gate(19, (u32_t)isr19);
    idt_set_gate(20, (u32_t)isr20);
    idt_set_gate(21, (u32_t)isr21);
    idt_set_gate(22, (u32_t)isr22);
    idt_set_gate(23, (u32_t)isr23);
    idt_set_gate(24, (u32_t)isr24);
    idt_set_gate(25, (u32_t)isr25);
    idt_set_gate(26, (u32_t)isr26);
    idt_set_gate(27, (u32_t)isr27);
    idt_set_gate(28, (u32_t)isr28);
    idt_set_gate(29, (u32_t)isr29);
    idt_set_gate(30, (u32_t)isr30);
    idt_set_gate(31, (u32_t)isr31);

    set_idt();
}

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t *r)
{
    kprint("Received interrupt: ", VGA_COLOR(BLACK, WHITE));
    char num[4];
    k_itoa(r->int_no, num);
    kprint(num, VGA_COLOR(BLACK, WHITE));
    kprint("\n", VGA_COLOR(BLACK, WHITE));
    kprint(exception_messages[r->int_no], VGA_COLOR(BLACK, WHITE));
    kprint("\n", VGA_COLOR(BLACK, WHITE));
}