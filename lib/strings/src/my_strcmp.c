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

int my_env_strcmp(char const *s1, char const *s2)
{
    int i = 0;
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);

    while ((i < len1 && i < len2) && s1[i] == s2[i]) {
        i++;
    }
    if (s1[i] == '=')
        return (0);
    return (s1[i] - s2[i]);
}
