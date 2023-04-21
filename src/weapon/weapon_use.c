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
#include "errorhandling.h"

void weapon_use(weapon_t *weapon, window_t *win, float delta)
{
    static sfTime prev_time = {0};
    sfTime time = {0};
    entity_t *entity = weapon->hitbox->owner;
    time = sfClock_getElapsedTime(win->frame);
    if (((time.microseconds - prev_time.microseconds) / 1000000. >
        weapon->cooldown / entity->stats.atk_speed || entity->dash.is_dashing)
        && sfMouse_isButtonPressed(sfMouseLeft)) {
        weapon->hitbox->activated = true;
        if (weapon->hitbox)
            weapon->hitbox->activated = true;
        prev_time = time;
    }
    if (weapon->hitbox->activated) {
        weapon->pos = sfView_getCenter(win->view);
        weapon->pos.y += 35;
        sfRectangleShape_setPosition(weapon->weapon, weapon->pos);
        sfRectangleShape_setRotation(weapon->weapon, weapon->angle + 45);
        weapon->rect = sfRectangleShape_getGlobalBounds(weapon->weapon);
        weapon->use(weapon, win, delta);
    }
}

static void rotate_sword(weapon_t *sword, sfVector2f player, float angle,
                        float ang_s)
{
    sfRectangleShape_setPosition(sword->weapon,
    (sfVector2f){player.x + ang_s *
    cos(angle * M_PI / 180) + 3, player.y + ang_s *
    sin(angle * M_PI / 180) + 39});
    sfRectangleShape_setRotation(sword->weapon, angle);
    sword->rect = sfRectangleShape_getGlobalBounds(sword->weapon);
}

static void check_restart(weapon_t *sword, bool *restart, float diff)
{
    if (diff >= 120.) {
        sword->hitbox->activated = false;
        *restart = true;
    }
}

void sword_use(weapon_t *sword, window_t *win, float delta)
{
    static float angle = 0;
    static float or_angle = 0;
    static float angular_speed = 0;
    static bool restart = true;
    sfVector2f player = {0};
    entity_t *owner = NULL;

    if (!sword)
        return;
    player = sfView_getCenter(win->view);
    if (restart) {
        owner = sword->hitbox->owner;
        angle = sword->angle - 30;
        or_angle = angle;
        angular_speed = 121 / (sword->cooldown / owner->stats.atk_speed / 2);
        restart = false;
    }
    check_restart(sword, &restart, angle - or_angle);
    rotate_sword(sword, player, angle, angular_speed * delta);
    angle += angular_speed * delta;
}
