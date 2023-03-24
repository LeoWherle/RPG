/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include "room.h"
#include "errorhandling.h"

int main(void)
{
    room_t *room = NULL;
    tile_t **tile_list = NULL;

    tile_list = init_tile_list(tile_list);
    ASSERT_MALLOC(tile_list, 84);
    room = get_room(room, EMPTY_R);
    ASSERT_MALLOC(room, 84);
    free_room(room);
    free_tile_list(tile_list);
    return 0;
}
