/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** village creation
*/

#include <stdlib.h>
#include "room.h"
#include "village.h"

static const sfFloatRect *vil_col_list[] = {
    &((sfFloatRect){0, 0, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0, 0 - 1.5, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0 - 0.75, -0.5, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0 + 0.75, -0.5, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0, 0 - 1.5, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0, 0 - 1.5, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){-1.2, -1, TILE_SIZE * 1.5, TILE_SIZE * 1.5}),
    &((sfFloatRect){1.2, -1, TILE_SIZE * 1.5, TILE_SIZE * 1.5}),
    &((sfFloatRect){0 - 1, 0 - 2, 0, 0}),
    &((sfFloatRect){0, 0 - 2, 0, 0}),
    &((sfFloatRect){0 - 0.5, 0, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0 + 0.5, 0, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0 - 3.5, 0 - 2.5, TILE_SIZE * 7, TILE_SIZE * 2.5}),
    &((sfFloatRect){0 - 0.9, 0 - 1.1, TILE_SIZE * 2.2, TILE_SIZE * 1.2}),
    &((sfFloatRect){0 - 0.3, 0, TILE_SIZE * 1.4, TILE_SIZE}),
    &((sfFloatRect){0 - 1.8, 0 - 1.2, TILE_SIZE * 4, TILE_SIZE * 1.5}),
    &((sfFloatRect){0 - 0.5, 0 - 0.6, TILE_SIZE * 1.5, TILE_SIZE}),
    &((sfFloatRect){0 - 1.5, 0 - 2.3, TILE_SIZE * 3.8, TILE_SIZE * 2.6}),
    &((sfFloatRect){0 - 0.3, 0 - 0.4, TILE_SIZE * 1.4, TILE_SIZE * 0.9}),
    &((sfFloatRect){0, 0, 0, 0}),
    &((sfFloatRect){0 - 0.2, -0.8, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0 - 0.3, 0 - 2, TILE_SIZE, TILE_SIZE * 4}),
    &((sfFloatRect){0 - 0.4, 0 - 0.75, TILE_SIZE * 1.4, TILE_SIZE * 0.9}),
    &((sfFloatRect){0 - 0.4, 0 - 0.75, TILE_SIZE * 1.4, TILE_SIZE * 0.9}),
    &((sfFloatRect){0, -1, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0, -1, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){-2.1, -4, TILE_SIZE * 4.6, TILE_SIZE * 4}),
    &((sfFloatRect){0 - 0.3, 0 - 0.4, TILE_SIZE * 1.3, TILE_SIZE * 0.7}),
    &((sfFloatRect){0 - 1.8, 0 - 1.2, TILE_SIZE * 4, TILE_SIZE * 1.5}),
    NULL};

sfFloatRect translate_collisions_village(char c)
{
    char img[] = "_-[]lrLR}{><MtTFfOvG+|bp\\/CVm";

    for (int i = 0; img[i] != '\0'; i++)
        if (img[i] == c)
            return (*vil_col_list[i]);
    return (*vil_col_list[0]);
}

int translate_village(char **map, int y, int x)
{
    char img[] = ". -_[]lrLR=/\\}{><MtTFfOvG+|,;:bpCVm";
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

tile_t **init_village_tile_list(tile_t **tile_list, int map_nb)
{
    char *tiles[] = {"assets/tiles/village.png", NULL};
    sfIntRect *rec_list[] = {&VOID_POS, &FLOOR_POS, &WALL_FRONT_POS,
    &WALL_BACK_POS, &WALL_LEFT_POS, &WALL_RIGHT_POS, &TOP_LEFT_POS,
    &TOP_RIGHT_POS, &BOT_LEFT_POS, &BOT_RIGHT_POS, &UNDER_GRASS_POS,
    &UNDER_GRASS_LEFT, &UNDER_GRASS_RIGHT, &INTERN_TOP_LEFT, &INTERN_TOP_RIGHT,
    &INTERN_BOT_LEFT, &INTERN_BOT_RIGHT, &TREE_HOUSE, &TREE_TRUNK, &TREE,
    &FRUIT_MERCHANT, &FLOWER_POT, &OBSERVATORY, &TUTORIAL_MAN, &BIG_HOLE,
    &HOLE_ISL, &BARRIER, &RED_FLOWER, &WHITE_FLOWER, &BLUE_FLOWER, &BUSH, &ROCK,
    &CAVE_TOWER, &MAN_BIRD, &SHOP, NULL};

    if (map_nb != 0)
        free(tile_list);
    tile_list = malloc(sizeof(tile_t *) * (TILE_NB_VILL + 1));
    ASSERT_MALLOC(tile_list, NULL);
    tile_list = fill_tile_list(tiles, tile_list, rec_list);
    ASSERT_MALLOC(tile_list, NULL);
    tile_list = set_origin(tile_list);
    return (tile_list);
}
