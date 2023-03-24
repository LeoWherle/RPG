/*
** EPITECH PROJECT, 2022
** my_nbrlen
** File description:
** get the len of a nb
*/

#include "my_str.h"

int my_nbrlen(long long n)
{
    int size = 1;
    long long nb = n;

    if (n < 0)
        size++;
    nb = ABS(n);
    while (nb != 0) {
        size++;
        nb = nb / 10;
    }
    if (n != 0)
        size--;
    return (size);
}
