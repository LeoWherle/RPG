/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** Cave generation
*/

#include <stdlib.h>
#include <time.h>
#include "room.h"
#include "cave.h"

static const sfFloatRect *vil_col_list[] = {
    &((sfFloatRect){0, -0.9, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0, -0.9, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0.35, -0.6, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){-0.35, -0.6, TILE_SIZE, TILE_SIZE}),
    &((sfFloatRect){0, 0 - 0.5, TILE_SIZE * 1.5, TILE_SIZE * 1.5}),
    &((sfFloatRect){-0.4, 0 - 0.5, TILE_SIZE * 1.5, TILE_SIZE * 1.5}),
    &((sfFloatRect){0, 0, TILE_SIZE * 1.5, TILE_SIZE * 1.5}),
    &((sfFloatRect){0, 0, TILE_SIZE * 1.5, TILE_SIZE * 1.5}),
    &((sfFloatRect){0, -0.9, TILE_SIZE * 2, TILE_SIZE}),
    &((sfFloatRect){0, -0.9, TILE_SIZE * 2, TILE_SIZE}),
    &((sfFloatRect){0, -0.9, TILE_SIZE * 2, TILE_SIZE}),
    &((sfFloatRect){0, -0.9, TILE_SIZE * 2, TILE_SIZE}),
    &((sfFloatRect){0 - 0.4, 0 - 0.75, TILE_SIZE * 1.7, TILE_SIZE * 0.9}),
    &((sfFloatRect){-0.3, -0.9, TILE_SIZE * 1.3, TILE_SIZE * 1.3}),
    &((sfFloatRect){0, -0.9, TILE_SIZE * 1.3, TILE_SIZE * 1.3}),
    &((sfFloatRect){-0.3, -0.9, TILE_SIZE * 1.3, TILE_SIZE}),
    &((sfFloatRect){0, -0.9, TILE_SIZE * 1.3, TILE_SIZE}),
    &((sfFloatRect){0, -0.9, TILE_SIZE * 2, TILE_SIZE}),
    &((sfFloatRect){0, -0.9, TILE_SIZE * 2, TILE_SIZE}),
    &((sfFloatRect){0, -0.9, TILE_SIZE * 2, TILE_SIZE}),
    &((sfFloatRect){0, -0.9, TILE_SIZE * 2, TILE_SIZE}),
    &((sfFloatRect){-0.3, 0, TILE_SIZE * 2, TILE_SIZE * 1.4}),
    &((sfFloatRect){-0.3, 0, TILE_SIZE * 2, TILE_SIZE * 1.4}),
    &((sfFloatRect){0.1, 0, TILE_SIZE * 0.9, TILE_SIZE * 0.5}),
    &((sfFloatRect){-2, -2, TILE_SIZE * 4, TILE_SIZE * 2}),
    NULL};

sfFloatRect trans_col_cave(char c)
{
    char img[] = "-_[]lrLRppPPc<>{}eeEESstX";

    for (int i = 0; img[i] != '\0'; i++)
        if (img[i] == c)
            return (*vil_col_list[i]);
    return (*vil_col_list[0]);
}

static int draw_doors(char **map, int x, int y, int i)
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

char *get_random_room(void)
{
    int nb = 0;
    char *path = NULL;

    nb = get_file_nb("assets/rooms/caves");
    if (nb <= 0)
        return (NULL);
    srand(time(NULL));
    nb = rand() % nb;
    path = get_specific_file("assets/rooms/caves", nb);
    return (path);
}

int translate_cave(char **map, int y, int x)
{
    char img[] = ". -_[]lrLRppPP:;,~c<>{}eeEESst";
    int i = 0;
    int temp = 0;

    if (map[y][x] == '$')
        return (FLOOR_ID);
    while (img[i] != '\0') {
        if (is_in(img[i], "pPeE") && (is_in(map[y][x], "pPeE"))
        && (temp = draw_doors(map, x, y, i)) != -1)
            return (temp);
        if (map[y][x] == img[i])
            return (i);
        i++;
    }
    return (VOID_ID);
}

tile_t **init_cave_tile_list(tile_t **tile_list, int map_nb)
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

    if (map_nb != 0)
        free(tile_list);
    tile_list = malloc(sizeof(tile_t *) * (TILE_NB_CAVE + 1));
    ASSERT_MALLOC(tile_list, NULL);
    tile_list = fill_tile_list(tiles, tile_list, rec_list);
    ASSERT_MALLOC(tile_list, NULL);
    return (tile_list);
}
