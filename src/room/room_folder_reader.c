/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** Room Folder reader
*/

#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include "errorhandling.h"
#include "my_str.h"

int get_file_nb(char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    int i = 0;

    dir = opendir(path);
    if (dir == NULL) return (-1);
    entry = readdir(dir);
    while (entry) {
        if (entry->d_name[0] == '.') {
            entry = readdir(dir);
            continue;
        }
        i++;
        entry = readdir(dir);
    }
    closedir(dir);
    return (i);
}

static char *create_room_path(char *room, char *path, struct dirent *entry)
{
    ASSERT_MALLOC(entry, NULL);
    room = malloc(sizeof(char) * (my_strlen(entry->d_name)
    + my_strlen(path) + 2));
    ASSERT_MALLOC(room, NULL);
    my_strcpy(room, path);
    my_strcat(room, "/");
    my_strcat(room, entry->d_name);
    return (room);
}

bool is_in(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return (true);
    }
    return (false);
}

char *get_specific_file(char *path, int nb)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    int i = 0;
    char *room = NULL;

    dir = opendir(path);
    ASSERT_MALLOC(dir, NULL);
    entry = readdir(dir);
    while (entry) {
        if (entry->d_name[0] == '.') {
            entry = readdir(dir);
            continue;
        }
        if (i == nb) break;
        i++;
        entry = readdir(dir);
    }
    room = create_room_path(room, path, entry);
    return (room);
}
