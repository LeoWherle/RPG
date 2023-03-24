/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** room manager
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <unistd.h>
#include <stdlib.h>
#include "room.h"
#include "my_str.h"
#include "errorhandling.h"

void free_room(room_t *room)
{
    int i = 0;

    while (room->room[i] != NULL) {
        free(room->room[i]);
        i++;
    }
    free(room->room);
    free(room);
}

void print_room(char **room)
{
    int i = 0;

    while (room[i] != NULL) {
        write(1, room[i], my_strlen(room[i]));
        write(1, "\n", 1);
        i++;
    }
}

static tile_t *init_collision(tile_t **tile, int i)
{
    if (i == VOID || i == WALL || i == DOOR)
        tile[i]->collision = true;
    else
        tile[i]->collision = false;
    return (tile[i]);
}

tile_t **init_tile_list(room_t *room, tile_t **tile_list)
{
    int i = 0;
    char *tiles[] = {"assets/tiles/void.png", "assets/tiles/floor.png",
    "assets/tiles/wall.png", "assets/tiles/door.png", NULL};

    tile_list = malloc(sizeof(tile_t *) * (TILE_NB + 1));
    ASSERT_MALLOC(tile_list, NULL);
    while (room->room[i] != NULL) {
        tile_list[i] = malloc(sizeof(tile_t));
        ASSERT_MALLOC(tile_list[i], NULL);
        tile_list[i]->texture = sfTexture_createFromFile(tiles[i], NULL);
        ASSERT_MALLOC(tile_list[i]->texture, NULL);
        tile_list[i]->img = sfSprite_create();
        ASSERT_MALLOC(tile_list[i]->img, NULL);
        sfSprite_setTexture(tile_list[i]->img, tile_list[i]->texture, sfTrue);
        tile_list[i] = init_collision(tile_list, i);
        i++;
    }
    tile_list[i] = NULL;
    return (tile_list);
}
