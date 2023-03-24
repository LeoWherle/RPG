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

    room = get_room(room, MONSTER);
    ASSERT_MALLOC(room, 84);
    print_room(room->room);
    free_room(room);
    return 0;
}
