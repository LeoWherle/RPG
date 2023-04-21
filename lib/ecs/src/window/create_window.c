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
    new->style = sfClose | sfResize;
    new->window = sfRenderWindow_create(new->mode, title,
    new->style, NULL);
    new->view = sfView_createFromRect(view_rect);
    new->event = malloc(sizeof(sfEvent));
    if (!new->window || !new->frame || !new->view || !new->event) {
        free(new);
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(new->window, framerate);
    sfRenderWindow_setView(new->window, new->view);
    new->exit = false;
    new->state = GAME;
    return new;
}

void window_destroy(window_t *window)
{
    sfClock_destroy(window->frame);
    sfRenderWindow_destroy(window->window);
    free(window->event);
    free(window);
}
