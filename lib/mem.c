#include "mem.h"

void memcpy(char *src, char *dest, int num_bytes)
{
    int i;
    for (i = 0; i < num_bytes; ++i) {
        *(dest + i) = *(src + i);
    }
}