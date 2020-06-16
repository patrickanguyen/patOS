#include "idt.h"

idt_entry_t idt_entries[NUM_IDT_ENTRIES];
idt_ptr_t idt_ptr;

#define LOW_16(num) (uint16_t)(num & 0xFFFF)
#define HIGH_16(num) (uint16_t)((num >> 16) & 0xFFF)

void idt_set_gate(int n, uint32_t handler)
{
    idt_entries[n].base_lo = LOW_16(handler);
    idt_entries[n].seg_select = KERNEL_CS;
    idt_entries[n].zero = 0;
    idt_entries[n].flags = 0x8E;
    idt_entries[n].base_hi = HIGH_16(handler);
}

void set_idt(void)
{
    idt_ptr.limit = sizeof(idt_entry_t) * NUM_IDT_ENTRIES -1;
    idt_ptr.base = (uint32_t) &idt_entries;

    __asm__ __volatile__("lidt (%0)" : : "r" (&idt_ptr));
}