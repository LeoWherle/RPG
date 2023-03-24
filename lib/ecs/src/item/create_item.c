/*
** EPITECH PROJECT, 2023
** create item
** File description:
** create an item
*/

#include <stdlib.h>
#include <stddef.h>
#include "item.h"

item_t *create_item(item_t *list, void *item, void (* update)(void *, sfEvent *),
                    void (* print)(void *, window_t *))
{
    item_t *new = NULL;

    new = malloc(sizeof(item_t));
    if (!new)
        return NULL;
    new->item = item;
    new->update = update;
    new->print = print;
    new->next = list;
    return new;
}
