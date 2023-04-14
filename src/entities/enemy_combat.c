/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** enemy combat
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "entities.h"

void enemy_invicibilty(entity_t *enemy, window_t *window)
{
    static sfTime time = {0};
    sfTime current = {0};

    if (time.microseconds == 0)
        time = sfClock_getElapsedTime(window->frame);
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - time.microseconds) / 1000000. > 0.2) {
        time.microseconds = 0;
        enemy->got_hit = false;
    }
}
