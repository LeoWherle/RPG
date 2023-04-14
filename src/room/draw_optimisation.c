/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** draw optimisation
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "room.h"

int stop_draw_on_close(window_t *window, int y)
{
    if (y % 5 == 0) {
        sfRenderWindow_pollEvent(window->window, window->event);
        if (window->event->type == sfEvtClosed)
            return (1);
    }
    return (0);
}

sfVector2f draw_in_rdr(sfVector2f center, int x, int y)
{
    sfVector2f pos = {0, 0};

    pos.x = x * TILE_SIZE;
    pos.y = y * TILE_SIZE;
    if (pos.x < center.x - RDR_DIST_X || pos.x > center.x + RDR_DIST_X
    || pos.y < center.y - RDR_DIST_Y || pos.y > center.y + RDR_DIST_Y)
        pos.x = -1;
    return (pos);
}

void draw_tile_on_floor(sfRenderWindow *window, sfSprite *floor, char c,
room_type_t type)
{
    if ((type == CAVE_R || type == BOSS_R) && !is_in(c, "?[]{}<>-_lrLR$@#"))
        sfRenderWindow_drawSprite(window, floor, NULL);
    if (type == VILLAGE_R && !is_in(c, "?+$@#w"))
        sfRenderWindow_drawSprite(window, floor, NULL);
    if (type == HOUSE_R && !is_in(c, "?$@"))
        sfRenderWindow_drawSprite(window, floor, NULL);
}

void draw_room_second(void *map_pt, window_t* window)
{
    sfVector2f pos = {0, 0};
    int tile_asset = 0;
    tile_t *tile = NULL;
    char c = 0;
    map_t *map = (map_t *)map_pt;
    sfVector2f center = sfView_getCenter(window->view);

    for (int y = 0; map->room->room[y] != NULL; y++) {
        if (stop_draw_on_close(window, y)) return;
        for (int x = 0; map->room->room[y][x] != '\0'; x++) {
            RENDER((pos = draw_in_rdr(center, x, y)).x);
            RENDER_3D(pos.y, center.y);
            tile_asset = translate_map(map->room->room, y, x, map->room->type);
            c = map->room->room[y][x];
            tile = map->tile_list[tile_asset];
            sfSprite_setPosition(tile->img, pos);
            draw_tile(window->window, tile->img, c, map->room->type);
        }
    }
}
