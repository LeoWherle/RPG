/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** ecs function for projectile
*/

#include "projectile.h"
#include "item.h"
#include "chained_list.h"

void projectile_update(void *item, window_t *window)
{
    list_t *list = item;
    node_t *node = list->head;
    projectile_t *proj = NULL;

    while (node) {
        proj = node->data;
        proj->move(proj, window);
        node = node->next;
    }
}

void projectile_print(void *item, window_t *window)
{
    list_t *list = item;
    node_t *node = list->head;
    projectile_t *proj = NULL;

    while (node) {
        proj = node->data;
        sfRenderWindow_drawRectangleShape(window->window, proj->rect, NULL);
        node = node->next;
    }
}
