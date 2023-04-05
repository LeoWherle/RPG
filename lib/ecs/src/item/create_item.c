/*
** EPITECH PROJECT, 2023
** create item
** File description:
** create an item
*/

#include <stdlib.h>
#include <stddef.h>
#include "item.h"

item_t *item_create(item_t *list, void *item, void (* destroy)(void *))
{
    item_t *new = NULL;

    new = malloc(sizeof(item_t));
    if (!new)
        return NULL;
    new->item = item;
    if (!new->item)
        return NULL;
    new->update = NULL;
    new->print = NULL;
    new->destroy = destroy;
    new->animate = NULL;
    new->next = list;
    return new;
}

void item_set_func(item_t *item, void (* update)(void *, window_t *),
                    void (* animate)(void *, sfTime *),
                    void (* print)(void *, window_t *))
{
    item->update = update;
    item->animate = animate;
    item->print = print;
}

void item_list_destroy(item_t *item)
{
    if (!item)
        return;
    item_list_destroy(item->next);
    if (item->destroy) {
        item->destroy(item->item);
        free(item);
    }
}
