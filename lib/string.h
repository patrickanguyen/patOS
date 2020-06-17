#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdbool.h>

void itoa(int n, char *str);
int atoi(const char *str);

size_t strlen(const char* s);
size_t strcmp(const char *s1, const char *s2);

bool isdigit(char c);
bool isalpha(char c);

#endif