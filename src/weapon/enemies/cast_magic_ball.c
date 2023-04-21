/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** cast magic ball
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <SFML/Graphics.h>
#include <math.h>
#include "errorhandling.h"
#include "weapon.h"
#include "collision.h"
#include "quick_create.h"
#include "entities.h"
#include "item.h"
#include "projectile.h"

static projectile_t *instantiate_magic_ball(weapon_t *ball, sfTexture *proj,
                                            entity_t *caster, window_t *win)
{
    projectile_t *new = NULL;

    new = projectile_create((sfFloatRect){caster->pos.x, caster->pos.y, 40, 40},
        (sfVector2f){10 / sin(M_PI / 2) * sin((M_PI / 2) -
        (ball->angle)), 10 / sin(M_PI / 2) * sin(ball->angle)},
        proj, projectile_move_line);
    if (!proj || !new) {
        win->state = EXIT_ERROR;
        return NULL;
    }
    new->move_vect.x /= (1. / 60.);
    new->move_vect.y /= (1. / 60.);
    sfRectangleShape_setRotation(new->rect, ball->angle);
    new->hitbox->owner = new;
    new->time.microseconds = 0;
    new->caster = ball->hitbox->owner;
    new->hitbox->on_collision_entered = projectile_collision;
        ball->hitbox->activated = false;
    return new;
}

void use_cast_magic_ball(weapon_t *ball, window_t *win, UNUSED float delta)
{
    entity_t *caster = NULL;
    sfTime time = sfTime_Zero;

    if (!ball)
        return;
    time = sfClock_getElapsedTime(win->frame);
    caster = ball->hitbox->owner;
    if (caster->enemy.spoted && (time.microseconds -
        caster->enemy.attack_time.microseconds) / 1000000. >
        ball->cooldown / caster->stats.atk_speed) {
        instantiate_magic_ball(ball, ball->texture, caster, win);
        caster->enemy.attack_time = time;
    }
}

weapon_t *cast_projectile(UNUSED sfVector2f size, int strength)
{
    weapon_t *new = NULL;

    new = malloc(sizeof(weapon_t));
    ASSERT_MALLOC(new, NULL);
    new->texture = sfTexture_createFromFile
    ("assets/items/Magic_ball.png", NULL);
    ASSERT_MALLOC(new->texture, NULL);
    new->weapon = rectangle_quick_create((sfFloatRect){0, 0, 0, 0},
                                        NULL, sfWhite);
    ASSERT_MALLOC(new->weapon, NULL;)
    new->rect = sfRectangleShape_getGlobalBounds(new->weapon);
    new->hitbox = collider_create(&new->rect, HITBOX, true, new);
    ASSERT_MALLOC(new->hitbox, NULL);
    new->angle = 0.;
    new->cooldown = 2.;
    new->strenght = strength;
    new->pos = (sfVector2f){0, 0};
    new->use = use_cast_magic_ball;
    new->path = NULL;
    return new;
}
