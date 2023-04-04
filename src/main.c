/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "room.h"
#include "errorhandling.h"

static void free_all(room_t *room, tile_t **tile_list, sfRenderWindow *window)
{
    free_room(room);
    free_tile_list(tile_list);
    sfRenderWindow_destroy(window);
}

static room_t *analyse_event(sfRenderWindow *window, room_t *room)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyR) {
            room = get_room(room, EMPTY_R);
            ASSERT_MALLOC(room, NULL);
        }
    }
    return (room);
}

static sfRenderWindow *create_win(sfRenderWindow *window)
{
    window = sfRenderWindow_create((sfVideoMode){1920, 1080, 32},
    "RPG", sfClose | sfResize, NULL);
    ASSERT_MALLOC(window, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    return (window);
}

int main(void)
{
    room_t *room = NULL;
    sfRenderWindow *window = NULL;
    tile_t **tile_list = NULL;

    tile_list = init_tile_list(tile_list);
    ASSERT_MALLOC(tile_list, 84);
    window = create_win(window);
    ASSERT_MALLOC(window, 84);
    room = get_room(room, EMPTY_R);
    ASSERT_MALLOC(room, 84);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, room->bg_color);
        draw_room(window, room, tile_list);
        room = analyse_event(window, room);
        ASSERT_MALLOC(room, 84);
        sfRenderWindow_display(window);
    }
    free_all(room, tile_list, window);
    return 0;
}
