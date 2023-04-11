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
    if (room->height <= 0)
        return (NULL);
    room->entity_nb = my_getnbr(&buff[4]);
    if (room->entity_nb <= 0)
        return (NULL);
    room->room = malloc(sizeof(char *) * (room->height + 1));
    ASSERT_MALLOC(room->room, NULL);
    return (room);
}

static room_t *fill_room_lines(room_t *room, char *buff, FILE *fd, size_t len)
{
    int y = 0;
    size_t c = 0;

    while ((int)c != -1 && buff != NULL && y < room->height) {
        c = getline(&buff, &len, fd);
        if ((int)c != -1 && buff[0] != '=') {
            room->room[y] = malloc(sizeof(char) * (c + 1));
            room->room[y] = fill_room(c, buff, room->room, y);
            ASSERT_MALLOC(room->room[y], NULL);
            y++;
        }
    }
    if (room->type == CAVE_R)
        room->bg_color = sfColor_fromRGB(34, 32, 52);
    if (room->type == VILLAGE_R)
        room->bg_color = sfColor_fromRGB(56, 152, 255);
    return (room);
}

static room_t *open_room(room_t *room, char *path, room_type_t type)
{
    FILE *fd = NULL;
    size_t len = 100;
    char *buff = NULL;

    room->height = 0;
    room->type = type;
    room->entity_nb = 0;
    fd = fopen(path, "r");
    ASSERT_MALLOC(fd, NULL);
    buff = malloc(sizeof(char) * len);
    ASSERT_MALLOC(buff, NULL);
    room = init_room(room, buff, fd, len);
    ASSERT_MALLOC(room, NULL);
    room = fill_room_lines(room, buff, fd, len);
    ASSERT_MALLOC(room, NULL);
    fclose(fd);
    free(buff);
    return (room);
}

room_t *get_room(room_t *room, room_type_t type)
{
    char *path = NULL;
    static int room_nb = 0;

    if (type == CAVE_R)
        path = get_random_room();
    if (type == VILLAGE_R)
        path = get_specific_file("assets/rooms/village", 0);
    ASSERT_MALLOC(path, NULL);
    if (room_nb != 0) free_room(room);
    room = malloc(sizeof(room_t));
    ASSERT_MALLOC(room, NULL);
    room = open_room(room, path, type);
    ASSERT_MALLOC(room, NULL);
    ASSERT_MALLOC(room->room, NULL);
    free(path);
    room_nb++;
    return (room);
}
