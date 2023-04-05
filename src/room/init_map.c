/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** init the map
*/

#include <stdlib.h>
#include "errorhandling.h"
#include "room.h"

void free_map(map_t *map)
{
    free_room(map->room);
    free_tile_list(map->tile_list);
    free(map);
}

map_t *init_map(map_t *map)
{
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