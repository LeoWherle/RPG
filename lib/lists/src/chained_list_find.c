/*
** EPITECH PROJECT, 2023
** graphical [WSL: fedora]
** File description:
** chained_list_utils
*/

#include <stdlib.h>
#include "chained_list.h"

/**
 * @brief find a node in a list
 *
 * @param list the list to search in
 * @param data the data to search for
 * @return node_t* the node containing the data
 */
node_t *node_find(list_t *list, const any_t data)
{
    node_t *node = NULL;
    int i = 0;

    node = list->head;
    while (i++ < list->size) {
        if (node->data == data) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

/**
 * @brief get a node at a specific index
 *
 * @param list the list to search in
 * @param index the index of the node
 * @return node_t* the node at the index or NULL if not found
 */
node_t *node_get(list_t *list, int index)
{
    node_t *node = NULL;
    int i = 0;

    node = list->head;
    while (i < list->size) {
        if (i == index) {
            return node;
        }
        i++;
        node = node->next;
    }
    return NULL;
}
