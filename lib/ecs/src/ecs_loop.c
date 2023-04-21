/*
** EPITECH PROJECT, 2023
** item
** File description:
** ECS loop
*/

#include <SFML/Graphics.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <stdio.h>
#include "item.h"

static void print(item_t *item, window_t *window)
{
    sfRenderWindow_clear(window->window, sfWhite);
    for (item_t *pr = item; pr; pr = pr->next) {
        if (pr->print)
            pr->print(pr->item, window);
    }
    sfRenderWindow_display(window->window);
}

static void execute(item_t *item, window_t *window, float delta)
{
    if (item) {
        execute(item->next, window, delta);
        if (window->state == EXIT_ERROR)
            return;
        if (item->update && window->event->type <= 23)
            item->update(item->item, window, delta);
        if (window->state == EXIT_ERROR)
            return;
        if (item->animate)
            item->animate(item->item, window);
    }
}

void item_loop(item_t *item, window_t *window, bool (* cond)(window_t *))
{
    sfTime time = {0};
    sfTime prev_time = {0};
    float delta = 0;

    prev_time = sfClock_getElapsedTime(window->frame);
    sfRenderWindow_pollEvent(window->window, window->event);
    while (!cond(window) && sfRenderWindow_isOpen(window->window)) {
        time = sfClock_getElapsedTime(window->frame);
        delta = (time.microseconds - prev_time.microseconds) / 1000000.;
        execute(item, window, delta);
        window->event->type = 23;
        if (window->state == EXIT_ERROR)
            return;
        print(item, window);
        prev_time = time;
        sfRenderWindow_pollEvent(window->window, window->event);
    }
}
