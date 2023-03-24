/*
** EPITECH PROJECT, 2023
** strcmp
** File description:
** Reproduce the behavior of the strcmp function.
*/
#include "my_str.h"

int my_strcmp(char const *s1, char const *s2)
{
    while (*s1 != '\0' && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*s1 == *s2) ? 0 : (*(unsigned char *)s1 - *(unsigned char *)s2);
}
