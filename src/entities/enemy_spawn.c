/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** enemy_spawn
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"
#include "collision.h"
#include "chained_list.h"
#include "errorhandling.h"
#include "item.h"
#include "room.h"

void enemy_list_print(void *enemies, window_t *window)
{
    list_t *list = (list_t *)enemies;
    item_t *enemy = NULL;
    node_t *node = list->head;

    while (node) {
        enemy = node->data;
        enemy->print(enemy->item, window);
        node = node->next;
    }
}

void enemy_list_animate(void *enemies, window_t *window)
{
    list_t *list = (list_t *)enemies;
    item_t *enemy = NULL;
    node_t *node = list->head;

    while (node) {
        enemy = node->data;
        enemy->animate(enemy->item, window);
        node = node->next;
    }
}

void enemy_list_update(void *enemies, window_t *window)
{
    list_t *list = (list_t *)enemies;
    item_t *enemy = NULL;
    entity_t *enemy_data = NULL;
    node_t *node = list->head;

    while (node) {
        enemy = node->data;
        enemy_data = enemy->item;
        enemy->update(enemy_data, window);
        node = node->next;
        if (enemy_data->stats.hp <= 0) {
            node_delete(list, enemy, destroy_item_enemy);
        }
    }
}
