/*
** EPITECH PROJECT, 2023
** mypaint [WSL: fedora]
** File description:
** test_list_exec
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "chained_list.h"

void ceasar_cipher(void *data)
{
    char *str = (char *)data;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = (str[i] - 'a' + 3) % 26 + 'a';
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = (str[i] - 'A' + 3) % 26 + 'A';
    }
}

void ceasar_cipher_m(void *data, void *arg, __attribute__((unused)) void *arg2)
{
    char *str = (char *)data;
    int shift = *(int *)arg;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = (str[i] - 'a' + shift) % 26 + 'a';
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = (str[i] - 'A' + shift) % 26 + 'A';
    }
}

Test(list_exec, test_list_exec)
{
    list_t *list = NULL;
    char *str = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    list = list_init();
    list->interface->append(list, str);
    list_foreach(list, ceasar_cipher);
    cr_assert_str_eq(list->head->data, "whvw");
}

Test(list_exec, test_list_exec_multiple)
{
    list_t *list = NULL;
    char *str1 = NULL;
    char *str2 = NULL;
    char *str3 = NULL;

    str1 = malloc(sizeof(char) * 6);
    strcpy(str1, "test1");
    str2 = malloc(sizeof(char) * 6);
    strcpy(str2, "test2");
    str3 = malloc(sizeof(char) * 6);
    strcpy(str3, "test3");
    list = list_init();
    list->interface->append(list, str1);
    list->interface->append(list, str2);
    list->interface->append(list, str3);
    list_foreach(list, ceasar_cipher);
    cr_assert_str_eq(list->head->data, "whvw1");
    cr_assert_str_eq(list->head->next->data, "whvw2");
    cr_assert_str_eq(list->head->next->next->data, "whvw3");
}

Test(list_exec_mulitple, test_list_exec_one)
{
    list_t *list = NULL;
    char *str = NULL;
    int shift = 4;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    list = list_init();
    list->interface->append(list, str);
    list_foreach_wargs(list, ceasar_cipher_m, &shift, NULL);
    cr_assert_str_eq(list->head->data, "xiwx");
}

Test(list_exec_mulitple, list_exec_multiple)
{
    list_t *list = NULL;
    char *str1 = NULL;
    char *str2 = NULL;
    char *str3 = NULL;
    int shift = 3;

    str1 = malloc(sizeof(char) * 6);
    strcpy(str1, "test1");
    str2 = malloc(sizeof(char) * 6);
    strcpy(str2, "test2");
    str3 = malloc(sizeof(char) * 6);
    strcpy(str3, "test3");
    list = list_init();
    list->interface->append(list, str1);
    list->interface->append(list, str2);
    list->interface->append(list, str3);
    list_foreach_wargs(list, ceasar_cipher_m, &shift, NULL);
    cr_assert_str_eq(list->head->data, "whvw1");
    cr_assert_str_eq(list->head->next->data, "whvw2");
    cr_assert_str_eq(list->head->next->next->data, "whvw3");
}