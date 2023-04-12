/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** combat
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "entities.h"
#include "collision.h"

sfFloatRect get_player_bounds(entity_t *player)
{
    sfFloatRect bounds;

    bounds = sfSprite_getGlobalBounds(player->sprite);
    bounds.left += 19;
    bounds.top += 23;
    bounds.width -= 19;
    bounds.height -= 8;
    return bounds;
}

void invicibility_frames(entity_t *player, window_t *window)
{
    static sfTime time = {0};
    static int is_invisible = true;
    sfTime current = {0};

    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - time.microseconds) / 1000000. > 0.15) {
        time = current;
        is_invisible = !is_invisible;
    }
    if (!is_invisible)
        sfRenderWindow_drawSprite(window->window, player->sprite, NULL);
}