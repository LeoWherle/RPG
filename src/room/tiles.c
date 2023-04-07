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

int draw_doors(char **map, int x, int y, int i)
{
    if (map[y][x] == 'p' && map[y - 1][x] == 'p')
        return (i + 1);
    if (map[y][x] == 'P' && map[y - 1][x] == 'P')
        return (i + 3);
    if (map[y][x] == 'e' && map[y + 1][x] == 'e')
        return (i + 14);
    if (map[y][x] == 'E' && map[y + 1][x] == 'E')
        return (i + 16);
    return (-1);
}

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

static tile_t **fill_tile_list(char **tiles, tile_t **tile_list,
sfIntRect *rec_list[])
{
    int i = 0;

    while (i < TILE_NB) {
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

tile_t **init_tile_list(tile_t **tile_list)
{
    char *tiles[] = {"assets/tiles/cave.png", NULL};
    sfIntRect *rec_list[] = {&VOID_POS, &FLOOR_POS,
    &WALL_FRONT_POS, &WALL_BACK_POS, &WALL_LEFT_POS, &WALL_RIGHT_POS,
    &TOP_LEFT_POS, &TOP_RIGHT_POS, &BOT_LEFT_POS, &BOT_RIGHT_POS,
    &DOOR_TOP_OP, &DOOR_BOT_OP, &DOOR_TOP_CL, &DOOR_BOT_CL, &LITTLE_CRIS_BL,
    &LITTLE_CRIS_PI, &LITTLE_ROCK, &LITTLE_STICK, &CHEST, &INTERN_TOP_LEFT,
    &INTERN_TOP_RIGHT, &INTERN_BOT_LEFT, &INTERN_BOT_RIGHT, &ENT_TOP_OP,
    &ENT_BOT_OP, &ENT_TOP_CL, &ENT_BOT_CL, &SAVE_PILLAR, &SAVED_PILLAR,
    &TORCH, NULL};

    tile_list = malloc(sizeof(tile_t *) * (TILE_NB + 1));
    ASSERT_MALLOC(tile_list, NULL);
    tile_list = fill_tile_list(tiles, tile_list, rec_list);
    ASSERT_MALLOC(tile_list, NULL);
    return (tile_list);
}
