#include "string.h"

static void reverse_str(char str[], int len);
static void swap(char *c1, char *c2);

void itoa(int n, char *str)
{
    int temp_num = n;
    bool is_negative = n < 0;

    if (is_negative) {
        temp_num *= -1;
    }

    if (n == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
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

size_t strlen(const char *s)
{
    size_t i = 0;

    while (s[i] != '\0') {
        ++i;
    }
    return i;
}

size_t strcmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return *(const unsigned char*) s1 - *(const unsigned char*)s2;
}

bool isdigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isalpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int atoi(const char *str)
{
    int result = 0;
    int i = 0;
    bool isNegative;

    /* Check if number is negative */
    if (str[0] == '-') {
        isNegative = 1;
        ++i;
    }
    else {  
        isNegative = 0;
    }

    while (str[i] != '\0') {
        /* Check if integer is valid */
        if (isdigit(str[i])) {
            int digit = str[i] - '0';
            result = result * 10 + digit;
        }
        else {
            return 0;
        }
        ++i;
    }

    return (isNegative) ? -result : result;

}

/* Helper functions definitions */

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