/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** init the map
*/

#include <stdlib.h>
#include "errorhandling.h"
#include "room.h"

void free_map(void *map_pt)
{
    map_t *map = (map_t *)map_pt;
    free_room(map->room);
    free_tile_list(map->tile_list);
    free(map);
}

map_t *init_map(void)
{
    map_t *map = NULL;

    map = malloc(sizeof(map_t));
    ASSERT_MALLOC(map, NULL);
    map->room = NULL;
    map->tile_list = NULL;
    map->tile_list = init_tile_list(map->tile_list);
    ASSERT_MALLOC(map->tile_list, NULL);
    map->room = get_room(map->room, EMPTY_R);
    ASSERT_MALLOC(map->room, NULL);
    return (map);
}
