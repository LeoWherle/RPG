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
    char *img = ". ";
    int i = 0;

    while (img[i] != '\0') {
        if (map[y][x] == img[i])
            return (i);
        i++;
    }
    return (VOID_ID);
}

tile_t **init_village_tile_list(tile_t **tile_list, int map_nb)
{
    char *tiles[] = {"assets/tiles/village.png", NULL};
    sfIntRect *rec_list[] = {&VOID_POS, &FLOOR_POS, NULL};

    if (map_nb != 0)
        free(tile_list);
    tile_list = malloc(sizeof(tile_t *) * (TILE_NB_VILL + 1));
    ASSERT_MALLOC(tile_list, NULL);
    tile_list = fill_tile_list(tiles, tile_list, rec_list);
    ASSERT_MALLOC(tile_list, NULL);
    return (tile_list);
}
