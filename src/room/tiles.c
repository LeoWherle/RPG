/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** tiles manager
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "room.h"
#include "errorhandling.h"

void free_tile_list(tile_t **tile_list)
{
    int i = 0;

    while (tile_list[i] != NULL) {
        sfTexture_destroy(tile_list[i]->texture);
        sfSprite_destroy(tile_list[i]->img);
        free(tile_list[i]);
        i++;
    }
    free(tile_list);
}

room_t *fill_collisions(room_t *room, char *buff, FILE *fd, size_t len)
{
    int y = 0;
    size_t c = 0;

    room->collisions = malloc(sizeof(char *) * (room->height + 1));
    ASSERT_MALLOC(room->collisions, NULL);
    while ((int)c != -1) {
        c = getline(&buff, &len, fd);
        if ((int)c != -1) {
            room->collisions[y] = malloc(sizeof(char) * (c + 1));
            room->collisions[y] = fill_room(c, buff, room->collisions, y);
            ASSERT_MALLOC(room->collisions[y], NULL);
            y++;
        }
    }
    return (room);
}

static int get_tile_nb(sfIntRect *rec_list[])
{
    int i = 0;

    while (rec_list[i] != NULL)
        i++;
    return (i);
}

tile_t **fill_tile_list(char **tiles, tile_t **tile_list, sfIntRect *rec_list[])
{
    int i = 0;
    int tile_nb = get_tile_nb(rec_list);

    while (i < tile_nb) {
        tile_list[i] = malloc(sizeof(tile_t));
        ASSERT_MALLOC(tile_list[i], NULL);
        tile_list[i]->texture = sfTexture_createFromFile(tiles[0], NULL);
        ASSERT_MALLOC(tile_list[i]->texture, NULL);
        tile_list[i]->img = sfSprite_create();
        ASSERT_MALLOC(tile_list[i]->img, NULL);
        sfSprite_setTexture(tile_list[i]->img, tile_list[i]->texture, sfTrue);
        sfSprite_setTextureRect(tile_list[i]->img, rec_list[i][0]);
        sfSprite_setScale(tile_list[i]->img, (sfVector2f){3, 3});
        i++;
    }
    tile_list[i] = NULL;
    return (tile_list);
}
