/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** room manager
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <unistd.h>
#include <stdlib.h>
#include "room.h"
#include "my_str.h"
#include "errorhandling.h"

list_t *handle_angle(list_t *colliders, room_t *room, int x, int y)
{
    if (room->room[y][x] == 'l') {
        room->room[y][x] = '[';
        add_in_colliders(colliders, room, x, y);
        ASSERT_MALLOC(colliders, NULL);
        room->room[y][x] = 'l';
    }
    if (room->room[y][x] == 'r') {
        room->room[y][x] = ']';
        add_in_colliders(colliders, room, x, y);
        ASSERT_MALLOC(colliders, NULL);
        room->room[y][x] = 'r';
    }
    return (colliders);
}

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
