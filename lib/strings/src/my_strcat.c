/*
** EPITECH PROJECT, 2022
** my_strcat.c
** File description:
** Write a function that concatenates two strings.
*/

#include "my_str.h"

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int dest_len = my_strlen(dest);

    while (src[i] != '\0') {
        dest[dest_len] = src[i];
        dest_len++;
        i++;
    }
    dest[dest_len] = '\0';
    return (dest);
}
