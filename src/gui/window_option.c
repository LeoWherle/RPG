/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** window option
*/

#include <SFML/Graphics.h>
#include "item.h"
#include "errorhandling.h"

static void reset_window(window_t *screen)
{
    sfRenderWindow_destroy(screen->window);
    screen->window = sfRenderWindow_create(screen->mode, "Into the abyss",
                                        screen->style, NULL);
    if (!screen->window) {
        screen->state = EXIT_ERROR;
        return;
    }
    sfRenderWindow_setFramerateLimit(screen->window, 60);
    sfRenderWindow_setView(screen->window, screen->view);
}

void set_fullscreen(UNUSED void *self, window_t *screen)
{
    if (screen->style == sfFullscreen)
        return;
    screen->style = sfFullscreen;
    reset_window(screen);
}

void set_normal_screen(UNUSED void *self, window_t *screen)
{
    if (screen->style == (sfClose | sfResize))
        return;
    screen->style = sfClose | sfResize;
    reset_window(screen);
}

void set_1920_1080(UNUSED void *self, window_t *screen)
{
    if (screen->mode.height == 1080 && screen->mode.width == 1920)
        return;
    screen->mode = (sfVideoMode){1920, 1080, 32};
    reset_window(screen);
}

void set_960_540(UNUSED void *self, window_t *screen)
{
    if (screen->mode.height == 960 && screen->mode.width == 540)
        return;
    screen->mode = (sfVideoMode){960, 540, 32};
    reset_window(screen);
}
