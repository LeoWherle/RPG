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

void execute(item_t *item, sfEvent *event, sfTime *time)
{
    if (item) {
        execute(item->next, event, time);
        if (item->update)
            item->update(item->item, event);
        if (item->animate)
            item->animate(item->item, time);
    }
    return;
}

void item_loop(item_t *item, window_t *window, bool (* cond)(sfEvent *))
{
    sfEvent event;
    sfTime time = {0};

    sfRenderWindow_pollEvent(window->window, &event);
    do {
        time = sfClock_getElapsedTime(window->frame);
        if (time.microseconds > window->framerate) {
            execute(item, &event, &time);
            print(item, window);
            sfClock_restart(window->frame);
        }
        sfRenderWindow_pollEvent(window->window, &event);
    } while (cond(&event));
}
