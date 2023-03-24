/*
** EPITECH PROJECT, 2023
** create window
** File description:
** create a window struct
*/

#include <stddef.h>
#include <stdlib.h>
#include <SFML/Window.h>
#include "item.h"

window_t *create_window(sfVideoMode mode, int framerate, char const *title)
{
    window_t *new = NULL;

    new = malloc(sizeof(window_t));
    if (!new)
        return NULL;
    new->frame = sfClock_create();
    new->framerate = 1. / framerate * 1000000.;
    new->mode = mode;
    new->window = sfRenderWindow_create(new->mode, title,
    sfClose | sfResize, NULL);
    if (!new->window) {
        free(new);
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(new->window, framerate);
    return new;
}
