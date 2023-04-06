/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** init the map
*/

#include <stdlib.h>
#include "errorhandling.h"
#include "room.h"
#include "cave.h"

void free_colliders(void *collider)
{
    collider_t *coll = (collider_t *)collider;

    free(coll);
}

void free_map(void *map_pt)
{
    map_t *map = (map_t *)map_pt;
    free_room(map->room);
    free_tile_list(map->tile_list);
    map->colliders->interface->destroy(map->colliders, free_colliders);
    free(map);
}

list_t *add_in_colliders(list_t *colliders, char **collisions, int x, int y)
{
    collider_t *collider = NULL;

    if (collisions[y][x] != '0') {
        collider = malloc(sizeof(collider_t));
        ASSERT_MALLOC(collider, NULL);
        collider = collider_create(&((sfFloatRect){x * TILE_SIZE, y *
        TILE_SIZE, TILE_SIZE, TILE_SIZE}), collisions[y][x] - '0',
        true, NULL);
        ASSERT_MALLOC(collider, NULL);
        colliders->interface->append(colliders, collider);
    }
    return (colliders);
}

list_t *init_colliders(list_t *colliders, char **collisions)
{
    colliders = list_init();
    ASSERT_MALLOC(colliders, NULL);
    for (int y = 0; collisions[y] != NULL; y++) {
        for (int x = 0; collisions[y][x] != '\0'; x++) {
            colliders = add_in_colliders(colliders, collisions, x, y);
            ASSERT_MALLOC(colliders, NULL);
        }
    }
    return (colliders);
}

map_t *init_map(room_type_t type)
{
    map_t *map = NULL;
    static int map_nb = 0;

    map = malloc(sizeof(map_t));
    ASSERT_MALLOC(map, NULL);
    map->room = NULL;
    map->tile_list = NULL;
    if (type == CAVE_R)
        map->tile_list = init_cave_tile_list(map->tile_list, map_nb);
    if (type == VILLAGE_R)
        map->tile_list = init_village_tile_list(map->tile_list, map_nb);
    ASSERT_MALLOC(map->tile_list, NULL);
    map->room = get_room(map->room, type);
    ASSERT_MALLOC(map->room, NULL);
    map->colliders = init_colliders(map->colliders, map->room->collisions);
    map_nb++;
    return (map);
}
