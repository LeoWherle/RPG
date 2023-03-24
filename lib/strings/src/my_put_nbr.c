/*
** EPITECH PROJECT, 2022
** my_put_nbr
** File description:
** Write a function that displays the number given as a parameter.
** It must be able to display all the possible
** values of an int
*/

#include "my_str.h"

long long signe_tester(long long nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb *= (-1);
    }
    return (nb);
}

void my_put_nbr(long long nb)
{
    long long temporary_nb1 = nb;
    long long size = 1;

    if (nb == 0)
        my_putchar('0');
    nb = signe_tester(nb);
    temporary_nb1 = nb;
    while (temporary_nb1 != 0) {
        temporary_nb1 = temporary_nb1 / 10;
        size = size * 10;
    }
    size = size / 10;
    temporary_nb1 = nb;
    while (size != 0) {
        temporary_nb1 = nb / size;
        my_putchar(temporary_nb1 + 48);
        nb = nb - temporary_nb1 * size;
        size = size / 10;
    }
}

void my_put_nbr_rec(long long int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb *= (-1);
    }
    if (nb >= 10)
        my_put_nbr_rec(nb / 10);
    my_putchar(nb % 10 + '0');
}
