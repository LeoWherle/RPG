/*
** EPITECH PROJECT, 2023
** create item
** File description:
** create an item
*/

#include <stdlib.h>
#include <stddef.h>
#include "item.h"

/**
 * @brief create an item
 *
 * @param list the list of item
 * @param item the object to be placed in the item struct
 * @param destroy a function to destroy the object
 * @return item_t*
 */
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

/**
 * @brief set the function pointer to the item struct
 *
 * @param item the item on wich the pointer will be set
 * @param update the update function of the item
 * @param animate the animate function of the item
 * @param print the print function of the item
 */
void item_set_func(item_t *item, void (* update)(void *, window_t *, float),
                    void (* animate)(void *, window_t *),
                    void (* print)(void *, window_t *))
{
    item->update = update;
    item->animate = animate;
    item->print = print;
}

/**
 * @brief destroy the given item list
 *
 * @param item the item_list to destroy
 */
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
