#ifndef IDT_H
#define IDT_H

#include "types.h"

#define NUM_IDT_ENTRIES 256
#define KERNEL_CS 0x08

/* Interrupt gate struct */
struct idt_entry{
    u16_t base_lo; /* Lower 16 bits of address to jump to after interrupt */
    u16_t seg_select; /* Kernel segment selector */
    u8_t zero; /* This must always be zero */
    u8_t flags; /* Flags */
    u16_t base_hi; /* Upper 16 bits of address to jump to */
} __attribute__((packed));

typedef struct idt_entry idt_entry_t;

/* Pointer to an array of interrupt handlers */
struct idt_ptr {
    u16_t limit;
    u32_t base; /* The address of the first element in our idt_entry_t array */
} __attribute__((packed));

typedef struct idt_ptr idt_ptr_t;

void set_idt(void);
void idt_set_gate(int n, u32_t handler);

#endif