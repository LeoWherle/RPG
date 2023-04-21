/*
** EPITECH PROJECT, 2022
** nbr_to_str
** File description:
** Write a function that displays the number given as a parameter.
** It must be able to display all the possible
** values of an int
*/

#include <stdlib.h>

int get_size(long long nb)
{
    int size = 1;

    while (nb != 0) {
        nb = nb / 10;
        size = size * 10;
    }
    size = size / 10;
    return (size);
}

char *nbr_to_str(long long nb)
{
    long long size = 1;
    int temp = 0;
    char *number = NULL;
    int i = 0;

    number = malloc(sizeof(char) * 9);
    if (nb == 0) { i++;
        number[0] = '0';
    }
    size = get_size(nb);
    while (size != 0) {
        temp = nb / size;
        number[i] = (temp + 48);
        nb = nb - temp * size;
        size = size / 10;
        i++;
    }
    number[i] = '\0';
    return (number);
}
