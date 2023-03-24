/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** room manager
*/

#include <unistd.h>
#include <stdlib.h>
#include "room.h"
#include "my_str.h"

void free_room(room_t *room)
{
    int i = 0;

    while (room->room[i] != NULL) {
        free(room->room[i]);
        i++;
    }
    free(room->room);
    free(room);
}

void print_room(char **room)
{
    int i = 0;

    while (room[i] != NULL) {
        write(1, room[i], my_strlen(room[i]));
        write(1, "\n", 1);
        i++;
    }
}
