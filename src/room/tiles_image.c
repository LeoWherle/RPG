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
#include "item.h"

static void draw_tile(sfRenderWindow *window, sfSprite *tile, char c)
{
    if (!is_in(c, "? "))
        sfRenderWindow_drawSprite(window, tile, NULL);
}

static void draw_floor_tile(sfRenderWindow *window, sfSprite *floor, char c)
{
    if (!is_in(c, "?[]{}<>-_lrLR"))
        sfRenderWindow_drawSprite(window, floor, NULL);
}

static void draw_floor(sfRenderWindow *window, room_t *room, tile_t **tile_list)
{
    sfVector2f pos = {0, 0};
    char c = 0;
    tile_t *floor = tile_list[FLOOR_ID];

    for (int y = 0; room->room[y] != NULL; y++) {
        for (int x = 0; room->room[y][x] != '\0'; x++) {
            pos.x = x * TILE_SIZE;
            pos.y = y * TILE_SIZE;
            c = room->room[y][x];
            sfSprite_setPosition(floor->img, pos);
            draw_floor_tile(window, floor->img, c);
        }
    }
}

static int translate_map(char **room, int y, int x, room_type_t type)
{
    int tile_asset = 0;

    if (type == CAVE_R)
        tile_asset = translate_cave(room, y, x);
    if (type == VILLAGE_R)
        tile_asset = translate_village(room, y, x);
    return (tile_asset);
}

void draw_room(void *map_pt, window_t* window)
{
    sfVector2f pos = {0, 0};
    int tile_asset = 0;
    tile_t *tile = NULL;
    char c = 0;
    map_t *map = (map_t *)map_pt;

    sfRenderWindow_clear(window->window, map->room->bg_color);
    draw_floor(window->window, map->room, map->tile_list);
    for (int y = 0; map->room->room[y] != NULL; y++) {
        for (int x = 0; map->room->room[y][x] != '\0'; x++) {
            pos.x = x * TILE_SIZE;
            pos.y = y * TILE_SIZE;
            tile_asset = translate_map(map->room->room, y, x, map->room->type);
            c = map->room->room[y][x];
            tile = map->tile_list[tile_asset];
            sfSprite_setPosition(tile->img, pos);
            draw_tile(window->window, tile->img, c);
        }
    }
}
