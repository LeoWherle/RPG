/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** weapon use
*/

#include <SFML/System.h>
#include <math.h>
#include <stdlib.h>
#include "weapon.h"
#include "item.h"
#include "entities.h"

void weapon_use(weapon_t *weapon, window_t *win)
{
    static sfTime prev_time = {0};
    sfTime time = {0};

    time = sfClock_getElapsedTime(win->frame);
    if ((time.microseconds - prev_time.microseconds) / 1000000. >
        weapon->cooldown && sfMouse_isButtonPressed(sfMouseLeft)) {
        weapon->activated = true;
        weapon->hitbox->activated = true;
        weapon->pos = sfView_getCenter(win->view);
        weapon->rect = sfRectangleShape_getGlobalBounds(weapon->weapon);
        prev_time = time;
    }
    if (weapon->activated)
        weapon->use(weapon, win);
}

void sword_use(weapon_t *sword, window_t *win)
{
    static float angle = 0;
    static sfTime prev_time = {0};
    sfTime time = {0};
    sfVector2f player = sfView_getCenter(win->view);
    if (prev_time.microseconds == 0) {
        prev_time = sfClock_getElapsedTime(win->frame);
        angle = sword->angle - 30;
    }
    time = sfClock_getElapsedTime(win->frame);
    if ((time.microseconds - prev_time.microseconds) / 1000000. > 0.23) {
        prev_time = time;
        sword->activated = false;
        prev_time.microseconds = 0;
    }
    sfRectangleShape_setPosition(sword->weapon, (sfVector2f){player.x +
        10 * cos(angle * M_PI / 180) + 3, player.y + 10 * sin(angle * M_PI /
        180) + 39});
    sfRectangleShape_setRotation(sword->weapon, angle);
    sword->rect = sfRectangleShape_getGlobalBounds(sword->weapon);
    angle += 10;
}
