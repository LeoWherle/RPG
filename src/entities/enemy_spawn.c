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

void destroy_monster(void *item)
{
    item_t *monster = (item_t *)item;

    item_list_destroy(monster);
}

void clear_list(void *list_void)
{
    list_t *list = (list_t *)list_void;

    list->interface->destroy(list, destroy_monster);
}

void enemy_type(list_t *enemies, int i, int j, char sign)
{
    item_t *add = NULL;

    if (sign == '#') {
        add = item_create(NULL,
        create_slime((sfVector2f){j * TILE_SIZE, i * TILE_SIZE}),
        destroy_enemy);
        if (!add)
            return;
        item_set_func(add, enemy_update, enemy_animation, enemy_print);
        enemies->interface->append(enemies, add);
    }
}

list_t *spawn_enemies(map_t *map)
{
    char **map_array = map->room->room;
    list_t *enemies = list_init();

    for (int i = 0; map_array[i] != NULL; i++) {
        for (int j = 0; map_array[i][j] != '\0'; j++) {
            enemy_type(enemies, i, j, map_array[i][j]);
        }
    }
    return enemies;
}

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
    node_t *node = list->head;

    while (node) {
        enemy = node->data;
        enemy->update(enemy->item, window);
        node = node->next;
    }
}