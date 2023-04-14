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

void draw_tile(sfRenderWindow *window, sfSprite *tile, char c,
room_type_t type)
{
    if ((type == CAVE_R || type == BOSS_R) && !is_in(c, "? $;,:~#@X"))
        sfRenderWindow_drawSprite(window, tile, NULL);
    if (type == VILLAGE_R && !is_in(c, "? []{}<>-_lrLR$;,:#@=/\\w"))
        sfRenderWindow_drawSprite(window, tile, NULL);
    if (type == HOUSE_R && !is_in(c, "? "))
        sfRenderWindow_drawSprite(window, tile, NULL);
}

static void draw_floor_tile(sfRenderWindow *window, sfSprite *floor, char c,
room_type_t type)
{
    if ((type == CAVE_R || type == BOSS_R) && !is_in(c, "?[]{}<>-_lrLRX"))
        sfRenderWindow_drawSprite(window, floor, NULL);
    if (type == VILLAGE_R && !is_in(c, "?=/\\+"))
        sfRenderWindow_drawSprite(window, floor, NULL);
    if (type == HOUSE_R && !is_in(c, "?"))
        sfRenderWindow_drawSprite(window, floor, NULL);
}

int translate_map(char **room, int y, int x, room_type_t type)
{
    int tile_asset = 0;

    if (type == CAVE_R || type == BOSS_R)
        tile_asset = translate_cave(room, y, x);
    if (type == VILLAGE_R)
        tile_asset = translate_village(room, y, x);
    if (type == HOUSE_R)
        tile_asset = translate_house(room, y, x);
    return (tile_asset);
}

static void draw_floor(window_t *window, room_t *room, tile_t **tile_list)
{
    sfVector2f pos = {0, 0};
    char c = 0;
    tile_t *floor = tile_list[FLOOR_ID];
    tile_t *tile = NULL;
    int tile_asset = 0;
    sfVector2f center = sfView_getCenter(window->view);

    for (int y = 0; room->room[y] != NULL; y++) {
        if (stop_draw_on_close(window, y)) return;
        for (int x = 0; room->room[y][x] != '\0'; x++) {
            RENDER((pos = draw_in_rdr(center, x, y)).x);
            c = room->room[y][x];
            sfSprite_setPosition(floor->img, pos);
            draw_floor_tile(window->window, floor->img, c, room->type);
            tile_asset = translate_map(room->room, y, x, room->type);
            tile = tile_list[tile_asset];
            sfSprite_setPosition(tile->img, pos);
            draw_tile_on_floor(window->window, tile->img, c, room->type);
        }
    }
}

void draw_room_first(void *map_pt, window_t* window)
{
    sfVector2f pos = {0, 0};
    int tile_asset = 0;
    char c = 0;
    map_t *map = (map_t *)map_pt;
    sfVector2f center = sfView_getCenter(window->view);

    sfRenderWindow_clear(window->window, map->room->bg_color);
    draw_floor(window, map->room, map->tile_list);
    for (int y = 0; map->room->room[y] != NULL; y++) {
        if (stop_draw_on_close(window, y)) return;
        for (int x = 0; map->room->room[y][x] != '\0'; x++) {
            RENDER((pos = draw_in_rdr(center, x, y)).x);
            RENDER_3D(center.y, pos.y);
            tile_asset = translate_map(map->room->room, y, x, map->room->type);
            c = map->room->room[y][x];
            sfSprite_setPosition(map->tile_list[tile_asset]->img, pos);
            draw_tile(window->window, map->tile_list[tile_asset]->img, c,
            map->room->type);
        }
    }
}
