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
