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

window_t *window_create(sfVideoMode mode, int framerate, char const *title,
                        sfFloatRect view_rect)
{
    window_t *new = NULL;

    new = malloc(sizeof(window_t));
    if (!new)
        return NULL;
    new->frame = sfClock_create();
    new->mode = mode;
    new->freeze_frame = 0;
    new->window = sfRenderWindow_create(new->mode, title,
    sfClose | sfResize, NULL);
    new->view = sfView_createFromRect(view_rect);
    if (!new->window) {
        free(new);
        return NULL;
    }
    new->event = malloc(sizeof(sfEvent));
    sfRenderWindow_setFramerateLimit(new->window, framerate);
    sfRenderWindow_setView(new->window, new->view);
    return new;
}

void window_destroy(window_t *window)
{
    sfClock_destroy(window->frame);
    sfRenderWindow_destroy(window->window);
    free(window->event);
    free(window);
}
