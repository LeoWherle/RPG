/*
** EPITECH PROJECT, 2023
** minishell2 [WSL: fedora]
** File description:
** test_list_dup
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "chained_list.h"

Test(chained_list_dup, test_null)
{
    list_t *list = NULL;
    list_t *new_list = NULL;

    new_list = list_dup(list, NULL);
    cr_assert_null(new_list);
}

Test(chained_list_dup, test_empty)
{
    list_t *list = NULL;
    list_t *new_list = NULL;

    list = list_init();
    new_list = list_dup(list, NULL);
    cr_assert_not_null(new_list);
    cr_assert_eq(new_list->size, 0);
    cr_assert_null(new_list->head);
    cr_assert_null(new_list->tail);
    cr_assert_not_null(new_list->interface);
    cr_assert_not_null(new_list->interface->append);
    cr_assert_not_null(new_list->interface->insert);
    cr_assert_not_null(new_list->interface->popf);
    cr_assert_not_null(new_list->interface->pop);
    cr_assert_not_null(new_list->interface->append_list);
    cr_assert_not_null(new_list->interface->insert_list);
    cr_assert_not_null(new_list->interface->print);
    cr_assert_not_null(new_list->interface->find);
    cr_assert_not_null(new_list->interface->destroy);
}

Test(chained_list_dup, test_one_element)
{
    list_t *list = NULL;
    list_t *new_list = NULL;

    list = list_init();
    list->interface->insert(list, "END");
    new_list = list_dup(list, &string_dup);
    cr_assert_not_null(new_list);
    cr_assert_eq(new_list->size, 1);
    cr_assert_not_null(new_list->head);
    cr_assert_not_null(new_list->tail);
    cr_assert_str_eq(new_list->head->data, "END");
    cr_assert_str_eq(new_list->tail->data, "END");
    cr_assert_null(new_list->head->next);
    cr_assert_null(new_list->tail->next);
}

Test(chained_list_dup, test_two_elements)
{
    list_t *list = NULL;
    list_t *new_list = NULL;

    list = list_init();
    list->interface->insert(list, "END");
    list->interface->insert(list, "START");
    new_list = list_dup(list, &string_dup);
    cr_assert_not_null(new_list);
    cr_assert_eq(new_list->size, 2);
    cr_assert_not_null(new_list->head);
    cr_assert_not_null(new_list->tail);
    cr_assert_str_eq(new_list->head->data, "START");
    cr_assert_str_eq(new_list->tail->data, "END");
    cr_assert_not_null(new_list->head->next);
    cr_assert_null(new_list->tail->next);
    cr_assert_str_eq(new_list->head->next->data, "END");
}
