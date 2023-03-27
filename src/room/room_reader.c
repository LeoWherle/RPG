/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** room reader
*/

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "errorhandling.h"
#include "room.h"
#include "my_str.h"

char *fill_room(int c, char *buff, char **room, int y)
{
    ASSERT_MALLOC(room[y], NULL);
    my_strcpy(room[y], buff);
    room[y][c - 1] = '\0';
    room[y + 1] = NULL;
    return (room[y]);
}

static room_t *init_room(room_t *room, char *buff, FILE *fd, size_t len)
{
    size_t c = 0;

    c = getline(&buff, &len, fd);
    if ((int)c == -1)
        return (NULL);
    room->height = my_getnbr(buff);
    room->entity_nb = my_getnbr(&buff[4]);
    room->room = malloc(sizeof(char *) * (room->height + 1));
    ASSERT_MALLOC(room->room, NULL);
    return (room);
}

static room_t *fill_room_lines(room_t *room, char *buff, FILE *fd, size_t len)
{
    int y = 0;
    size_t c = 0;

    while ((int)c != -1 && (buff == NULL || buff[0] != '=')) {
        c = getline(&buff, &len, fd);
        if ((int)c != -1 && buff[0] != '=') {
            room->room[y] = malloc(sizeof(char) * (c + 1));
            room->room[y] = fill_room(c, buff, room->room, y);
            ASSERT_MALLOC(room->room[y], NULL);
            y++;
        }
    }
    room = fill_collisions(room, buff, fd, len);
    return (room);
}

static room_t *open_room(room_t *room, char *path)
{
    FILE *fd = NULL;
    size_t len = 100;
    char *buff = NULL;

    fd = fopen(path, "r");
    ASSERT_MALLOC(fd, NULL);
    buff = malloc(sizeof(char) * len);
    ASSERT_MALLOC(buff, NULL);
    room = init_room(room, buff, fd, len);
    ASSERT_MALLOC(room, NULL);
    room = fill_room_lines(room, buff, fd, len);
    fclose(fd);
    free(buff);
    return (room);
}

room_t *get_room(room_t *room, room_type_t type)
{
    char *path = NULL;
    int nb = get_file_nb("assets/rooms/dungeon");
    static int room_nb = 0;

    if (nb <= 0) return (NULL);
    srand(time(NULL));
    nb = rand() % nb;
    path = get_specific_file("assets/rooms/dungeon", nb);
    ASSERT_MALLOC(path, NULL);
    if (room_nb != 0) free_room(room);
    room = malloc(sizeof(room_t));
    room->type = type;
    room->entity_nb = 0;
    ASSERT_MALLOC(room, NULL);
    room = open_room(room, path);
    ASSERT_MALLOC(room->room, NULL);
    ASSERT_MALLOC(room->collisions, NULL);
    free(path);
    room_nb++;
    return (room);
}
