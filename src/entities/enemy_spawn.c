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
#include "item.h"
#include "room.h"

void clear_list(list_t *list)
{
    list->interface->destroy(list, destroy_enemy);
}

void enemy_type(list_t *enemies, int i, int j, char sign)
{
    if (sign == '#') {
        enemies->interface->append(enemies,
        create_slime((sfVector2f){j * TILE_SIZE, i * TILE_SIZE}));
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