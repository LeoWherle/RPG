/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** tiles image manager
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <unistd.h>
#include <stdlib.h>
#include "room.h"
#include "errorhandling.h"

static int translate_map(char **map, int y, int x)
{
    char *img = ". -[]lrLRpPc}{Ssf/";
    int i = 0;

    while (img[i] != '\0') {
        if (map[y][x] == img[i])
            return (i);
        i++;
    }
    if (map[y][x] == 'E' || map[y][x] == '$')
        return (translate_map(map, y, x + 1));
    return (0);
}

static void draw_tile(sfRenderWindow *window, sfSprite *tile, sfSprite *floor,
char c)
{

    if (c == 'c' || c == '[' || c == ']') {
        sfRenderWindow_drawSprite(window, floor, NULL);
    }
    if (c != '?')
        sfRenderWindow_drawSprite(window, tile, NULL);
}

void draw_room(sfRenderWindow *window, room_t *room, tile_t **tile_list)
{
    sfVector2f pos = {0, 0};
    int tile_asset = 0;
    tile_t *tile = NULL;
    char c = 0;
    tile_t *floor = tile_list[FLOOR];

    for (int y = 0; room->room[y] != NULL; y++) {
        for (int x = 0; room->room[y][x] != '\0'; x++) {
            pos.x = x * TILE_SIZE;
            pos.y = y * TILE_SIZE;
            tile_asset = translate_map(room->room, y, x);
            c = room->room[y][x];
            tile = tile_list[tile_asset];
            sfSprite_setPosition(floor->img, pos);
            sfSprite_setPosition(tile->img, pos);
            draw_tile(window, tile->img, floor->img, c);
        }
    }
}
