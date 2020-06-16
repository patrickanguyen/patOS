#include "isr.h"
#include "idt.h"
#include "ports.h"
#include "../drivers/screen.h"
#include "timer.h"
#include "../drivers/keyboard.h"
#include "../kernel/util.h"
#include <stdint.h>

isr_t interrupt_handlers[256];

void isr_install() 
{
    idt_set_gate(0, (uint32_t)isr0);
    idt_set_gate(1, (uint32_t)isr1);
    idt_set_gate(2, (uint32_t)isr2);
    idt_set_gate(3, (uint32_t)isr3);
    idt_set_gate(4, (uint32_t)isr4);
    idt_set_gate(5, (uint32_t)isr5);
    idt_set_gate(6, (uint32_t)isr6);
    idt_set_gate(7, (uint32_t)isr7);
    idt_set_gate(8, (uint32_t)isr8);
    idt_set_gate(9, (uint32_t)isr9);
    idt_set_gate(10, (uint32_t)isr10);
    idt_set_gate(11, (uint32_t)isr11);
    idt_set_gate(12, (uint32_t)isr12);
    idt_set_gate(13, (uint32_t)isr13);
    idt_set_gate(14, (uint32_t)isr14);
    idt_set_gate(15, (uint32_t)isr15);
    idt_set_gate(16, (uint32_t)isr16);
    idt_set_gate(17, (uint32_t)isr17);
    idt_set_gate(18, (uint32_t)isr18);
    idt_set_gate(19, (uint32_t)isr19);
    idt_set_gate(20, (uint32_t)isr20);
    idt_set_gate(21, (uint32_t)isr21);
    idt_set_gate(22, (uint32_t)isr22);
    idt_set_gate(23, (uint32_t)isr23);
    idt_set_gate(24, (uint32_t)isr24);
    idt_set_gate(25, (uint32_t)isr25);
    idt_set_gate(26, (uint32_t)isr26);
    idt_set_gate(27, (uint32_t)isr27);
    idt_set_gate(28, (uint32_t)isr28);
    idt_set_gate(29, (uint32_t)isr29);
    idt_set_gate(30, (uint32_t)isr30);
    idt_set_gate(31, (uint32_t)isr31);

    /* Remap PIC */
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0); 

    idt_set_gate(32, (uint32_t)irq0);
    idt_set_gate(33, (uint32_t)irq1);
    idt_set_gate(34, (uint32_t)irq2);
    idt_set_gate(35, (uint32_t)irq3);
    idt_set_gate(36, (uint32_t)irq4);
    idt_set_gate(37, (uint32_t)irq5);
    idt_set_gate(38, (uint32_t)irq6);
    idt_set_gate(39, (uint32_t)irq7);
    idt_set_gate(40, (uint32_t)irq8);
    idt_set_gate(41, (uint32_t)irq9);
    idt_set_gate(42, (uint32_t)irq10);
    idt_set_gate(43, (uint32_t)irq11);
    idt_set_gate(44, (uint32_t)irq12);
    idt_set_gate(45, (uint32_t)irq13);
    idt_set_gate(46, (uint32_t)irq14);
    idt_set_gate(47, (uint32_t)irq15);

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

void register_interrupt_handler(uint8_t n, isr_t handler) 
{
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t *r) 
{
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r->int_no >= 40) {
        port_byte_out(0xA0, 0x20); /* slave */
    }
    port_byte_out(0x20, 0x20); /* master */

    /* Handle the interrupt */
    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }
}

void irq_install(void)
{
    __asm__ __volatile__("sti");
    init_timer(50);
    init_keyboard();
}