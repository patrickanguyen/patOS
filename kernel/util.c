#include "util.h"

static void swap(char *c1, char *c2);
static void reverse_str(char str[], int len);

void k_memcpy(char *src, char *dest, int num_bytes)
{
    int i;
    for (i = 0; i < num_bytes; ++i) {
        *(dest + i) = *(src + i);
    }
}

void k_itoa(int n, char str[])
{
    int is_negative = n < 0;

    if (is_negative) {
        n *= -1;
    }

    if (n == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    int temp_num = n;
    int i = 0;

    while (temp_num != 0) {
        int digit = temp_num % 10;
        str[i++] = digit + '0';
        temp_num /= 10;
    }
    
    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse_str(str, i);
}

static void reverse_str(char str[], int len)
{
    int i = 0;
    int j = len - 1;

    while (i < j) {
        swap(&str[i], &str[j]);
        i++;
        j--;
    }
}

static void swap(char *c1, char *c2)
{
    char temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}