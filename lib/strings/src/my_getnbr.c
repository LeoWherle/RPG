/*
** EPITECH PROJECT, 2022
** my_getnbr
** File description:
** Write a function that returns a number, sent to
** the function as a string.
*/

#include <stddef.h>

static int my_is_nbr(const char c)
{
    return ((c >= '0') && (c <= '9'));
}

int my_getnbr(char const *str)
{
    long number = 0;
    int sign = 1;

    if (str == NULL)
        return 0;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str && my_is_nbr(*str)) {
        number = number * 10 + *str - '0';
        str++;
    }
    return (number * sign);
}
