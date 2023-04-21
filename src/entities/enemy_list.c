/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** enemy list
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

void destroy_item_enemy(void *item)
{
    item_t *monster = (item_t *)item;

    item_list_destroy(monster);
}

void clear_list(void *list_void)
{
    list_t *list = (list_t *)list_void;

    list->interface->destroy(list, destroy_item_enemy);
}

void clear_enemies(list_t *enemies)
{
    list_t *list = (list_t *)enemies;
    item_t *enemy = NULL;
    node_t *node = list->head;

    while (node) {
        enemy = node->data;
        node = node->next;
        node_delete(list, enemy, destroy_item_enemy);
    }
}

bool enemy_type(list_t *enemies, int i, int j, char sign)
{
    if (!enemy_set(enemies, i, j, sign))
        return false;
    return true;
}

list_t *spawn_enemies(map_t *map)
{
    char **map_array = NULL;
    static list_t *enemies = NULL;
    bool error = true;

    if (enemies)
        clear_enemies(enemies);
    if (!enemies)
        enemies = list_init();
    if (!enemies || !map)
        return false;
    map_array = map->room->room;
    for (int i = 0; map_array[i] != NULL && error; i++) {
        for (int j = 0; map_array[i][j] != '\0' && error; j++) {
            error = enemy_type(enemies, i, j, map_array[i][j]);
        }
    }
    if (!error)
        return NULL;
    return enemies;
}
