/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** village creation
*/

#include <stdlib.h>
#include "room.h"
#include "village.h"

int translate_village(char **map, int y, int x)
{
    char *img = ". -_[]lrLR=/\\}{><MtTFfOvG+|,;:bp";
    int i = 0;

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
    NULL};

    if (map_nb != 0)
        free(tile_list);
    tile_list = malloc(sizeof(tile_t *) * (TILE_NB_VILL + 1));
    ASSERT_MALLOC(tile_list, NULL);
    tile_list = fill_tile_list(tiles, tile_list, rec_list);
    ASSERT_MALLOC(tile_list, NULL);
    tile_list = set_origin(tile_list);
    return (tile_list);
}
