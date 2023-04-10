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
        sfRectangleShape_setRotation(weapon->weapon, weapon->angle + 90.);
        weapon->pos = sfView_getCenter(win->view);
        weapon->rect = sfRectangleShape_getGlobalBounds(weapon->weapon);
        prev_time = time;
    }
    if (weapon->activated)
        weapon->use(weapon, win);
}

void lance_use(weapon_t *lance, window_t *win)
{
    static sfTime prev_time = {0};
    static sfVector2f velocity = {0};
    sfTime time = {0};

    time = sfClock_getElapsedTime(win->frame);
    if (velocity.x == 0 && velocity.y == 0) {
        prev_time = sfClock_getElapsedTime(win->frame);
        velocity.x = 5. / sin(M_PI / 2) * sin((M_PI / 2) - (lance->angle * M_PI / 180.));
        velocity.y = 5. / sin(M_PI / 2) * sin(lance->angle * M_PI / 180.);
    }
    if ((time.microseconds - prev_time.microseconds) / 1000000. > 0.2) {
        lance->activated = false;
        lance->hitbox->activated = false;
        velocity = (sfVector2f){0, 0};
    }
    lance->pos.x += velocity.x;
    lance->pos.y += velocity.y;
    sfRectangleShape_setPosition(lance->weapon, lance->pos);
    lance->rect = sfRectangleShape_getGlobalBounds(lance->weapon);
}
