#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define NUM_IDT_ENTRIES 256
#define KERNEL_CS 0x08

/* Interrupt gate struct */
struct idt_entry{
    uint16_t base_lo; /* Lower 16 bits of address to jump to after interrupt */
    uint16_t seg_select; /* Kernel segment selector */
    uint8_t zero; /* This must always be zero */
    uint8_t flags; /* Flags */
    uint16_t base_hi; /* Upper 16 bits of address to jump to */
} __attribute__((packed));

typedef struct idt_entry idt_entry_t;

/* Pointer to an array of interrupt handlers */
struct idt_ptr {
    uint16_t limit;
    uint32_t base; /* The address of the first element in our idt_entry_t array */
} __attribute__((packed));

typedef struct idt_ptr idt_ptr_t;

void set_idt(void);
void idt_set_gate(int n, uint32_t handler);

#endif