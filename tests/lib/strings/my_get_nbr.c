/*
** EPITECH PROJECT, 2023
** lemin [WSL: fedora]
** File description:
** my_get_nbr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_str.h"

char *neg = "-45";
char *pos = "399";
char *zero = "0";
char *random_text = "sfqdq";
char *pos_random = "33sdfq";

Test(string_getnbr, null)
{
    int value = 4;

    value = my_getnbr(NULL);
    cr_assert_eq(value, 0);
}

Test(string_getnbr, empty)
{
    int value = 0;

    value = my_getnbr("");
    cr_assert_eq(value, 0);
}

Test(string_getnbr, positive_number)
{
    int value = 0;

    value = my_getnbr(pos);
    cr_assert_eq(value, 399);
}

Test(string_getnbr, negative_number)
{
    int value = 0;

    value = my_getnbr(neg);
    cr_assert_eq(value, -45);
}

Test(string_getnbrn, text)
{
    int value = 0;

    value = my_getnbr(random_text);
    cr_assert_eq(value, 0);
}

Test(string_get_nbr, pos_random)
{
    int value = 0;

    value = my_getnbr(pos_random);
    cr_assert_eq(value, 33);
}