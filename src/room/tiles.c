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

tile_t **fill_tile_list(char **tiles, tile_t **tile_list)
{
    int i = 0;

    while (i < TILE_NB) {
        tile_list[i] = malloc(sizeof(tile_t));
        ASSERT_MALLOC(tile_list[i], NULL);
        tile_list[i]->texture = sfTexture_createFromFile(tiles[i], NULL);
        ASSERT_MALLOC(tile_list[i]->texture, NULL);
        tile_list[i]->img = sfSprite_create();
        ASSERT_MALLOC(tile_list[i]->img, NULL);
        sfSprite_setTexture(tile_list[i]->img, tile_list[i]->texture, sfTrue);
        sfSprite_setScale(tile_list[i]->img, (sfVector2f){4, 4});
        i++;
    }
    tile_list[i] = NULL;
    return (tile_list);
}

tile_t **init_tile_list(tile_t **tile_list)
{
    char *tiles[] = {"assets/tiles/void.png", "assets/tiles/floor.png",
    "assets/tiles/wall.png", "assets/tiles/wall2.png",
    "assets/tiles/wall3.png", "assets/tiles/up_left.png",
    "assets/tiles/up_right.png", "assets/tiles/down_left.png",
    "assets/tiles/down_right.png", "assets/tiles/door.png",
    "assets/tiles/open_door.png", "assets/tiles/chest.png",
    "assets/tiles/wall2.png", "assets/tiles/wall3.png",
    "assets/tiles/spikes_up.png", "assets/tiles/spikes_down.png",
    "assets/tiles/fire_statue.png", NULL};

    tile_list = malloc(sizeof(tile_t *) * (TILE_NB + 1));
    ASSERT_MALLOC(tile_list, NULL);
    tile_list = fill_tile_list(tiles, tile_list);
    ASSERT_MALLOC(tile_list, NULL);
    return (tile_list);
}
