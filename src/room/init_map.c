/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** init the map
*/

#include <stdlib.h>
#include "errorhandling.h"
#include "room.h"
#include "collision.h"

void free_colliders(void *collider)
{
    collider_t *coll = (collider_t *)collider;

    collider_destroy(coll);
}

void free_map(void *map_pt)
{
    map_t *map = (map_t *)map_pt;

    if (!map)
        return;
    if (map->room)
        free_room(map->room);
    if (map->tile_list)
        free_tile_list(map->tile_list);
    if (map->colliders)
        map->colliders->interface->destroy(map->colliders, free_colliders);
    free(map);
}

static map_t *reset_map(map_t *map)
{
    if (map != NULL && map->colliders != NULL) {
        map->colliders->interface->destroy(map->colliders, free_colliders);
        map->colliders = NULL;
    }
    if (map == NULL) {
        map = malloc(sizeof(map_t));
        ASSERT_MALLOC(map, NULL);
        map->room = NULL;
        map->tile_list = NULL;
        map->colliders = NULL;
    }
    return (map);
}

map_t *init_map(room_type_t type, map_t *map)
{
    static int map_nb = 0;

    map = reset_map(map);
    ASSERT_MALLOC(map, NULL);
    if (type == CAVE_R || type == BOSS_R)
        map->tile_list = init_cave_tile_list(map->tile_list, map_nb);
    if (type == VILLAGE_R)
        map->tile_list = init_village_tile_list(map->tile_list, map_nb);
    if (type == HOUSE_R)
        map->tile_list = init_house_tile_list(map->tile_list, map_nb);
    ASSERT_MALLOC(map->tile_list, NULL);
    map->room = get_room(map->room, type);
    ASSERT_MALLOC(map->room, NULL);
    map->colliders = init_colliders(map->colliders, map->room);
    ASSERT_MALLOC(map->colliders, NULL);
    map_nb++;
    return (map);
}
