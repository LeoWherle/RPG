/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** house creation
*/

#include <stdlib.h>
#include "room.h"
#include "house.h"

static const sfFloatRect *house_col_list[] = {
    &((sfFloatRect){0, -0.7, TILE_SIZE * 1.6, TILE_SIZE * 2}),
    &((sfFloatRect){0 - 0.3, 0 - 0.5, TILE_SIZE * 1.5, TILE_SIZE * 0.5}),
    &((sfFloatRect){-1, -1, TILE_SIZE * 2.2, TILE_SIZE * 1.2}),
    &((sfFloatRect){-0.2, -1.2, TILE_SIZE * 1.8, TILE_SIZE * 2}),
    &((sfFloatRect){0, -2, TILE_SIZE, TILE_SIZE}),
    NULL};

sfFloatRect translate_collisions_house(char c)
{
    char img[] = "bcAX@";

    for (int i = 0; img[i] != '\0'; i++)
        if (img[i] == c)
            return (*house_col_list[i]);
    return (*house_col_list[0]);
}

int translate_house(char **map, int y, int x)
{
    char img[] = ".. bcAX";
    int i = 0;

    if (map[y][x] == '$')
        return (FLOOR_ID);
    while (img[i] != '\0') {
        if (map[y][x] == img[i])
            return (i);
        i++;
    }
    return (VOID_ID);
}

sfFloatRect *translate_collisions(char c, sfFloatRect *rect, room_type_t type)
{
    if (type == VILLAGE_R)
        *rect = translate_collisions_village(c);
    if (type == CAVE_R || type == BOSS_R)
        *rect = trans_col_cave(c);
    if (type == HOUSE_R)
        *rect = translate_collisions_house(c);
    return (rect);
}

static tile_t **set_origin(tile_t **tile_list)
{
    sfVector2f origin = {0, 0};
    sfIntRect rect = {0, 0, 0, 0};

    for (int i = 0; tile_list[i] != NULL; i++) {
        rect = sfSprite_getTextureRect(tile_list[i]->img);
        if (rect.width > 20) {
            origin.y = rect.height - 20;
            origin.x = rect.width / 2 - 5;
            sfSprite_setOrigin(tile_list[i]->img, origin);
        }
    }
    return (tile_list);
}

tile_t **init_house_tile_list(tile_t **tile_list, int map_nb)
{
    char *tiles[] = {"assets/tiles/bedroom.png", NULL};
    sfIntRect *rec_list[] = {&VOID_POS, &FLOOR_POS, &ROOM_POS, &BED_POS,
    &CHEST_POS, &CABINET_POS, &SOLID_POS, NULL};

    if (map_nb != 0)
        free(tile_list);
    tile_list = malloc(sizeof(tile_t *) * (TILE_NB_VILL + 1));
    ASSERT_MALLOC(tile_list, NULL);
    tile_list = fill_tile_list(tiles, tile_list, rec_list);
    ASSERT_MALLOC(tile_list, NULL);
    tile_list = set_origin(tile_list);
    return (tile_list);
}
