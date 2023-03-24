/*
** EPITECH PROJECT, 2022
** my_putchar
** File description:
** write character
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1,  &c,1 );
}
