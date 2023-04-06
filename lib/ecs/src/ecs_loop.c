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

void print(item_t *item, window_t *window)
{
    sfRenderWindow_clear(window->window, sfWhite);
    for (item_t *pr = item; pr; pr = pr->next) {
        if (pr->item)
            pr->print(pr->item, window);
    }
    sfRenderWindow_display(window->window);
}

void execute(item_t *item, sfTime *time, window_t *window)
{
    if (item) {
        execute(item->next, time, window);
        if (item->update && window->event->type <= 23)
            item->update(item->item, window);
        if (item->animate)
            item->animate(item->item, time);
    }
}

void item_loop(item_t *item, window_t *window, bool (* cond)(window_t *))
{
    sfTime time = {0};
    sfTime prev_time = {0};

    prev_time = sfClock_getElapsedTime(window->frame);
    sfRenderWindow_pollEvent(window->window, window->event);
    do {
        time = sfClock_getElapsedTime(window->frame);
        if ((time.microseconds - prev_time.microseconds) / 1000000. >
            0.016666) {
            execute(item, &time, window);
            print(item, window);
            time = prev_time;
        }
        sfRenderWindow_pollEvent(window->window, window->event);
    } while (!cond(window));
}
