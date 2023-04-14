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
#include "weapon.h"
#include "collision.h"
#include "quick_create.h"
#include "entities.h"
#include "item.h"
#include "projectile.h"

static projectile_t *instantiate_magic_ball(weapon_t *ball, sfTexture *proj)
{
    projectile_t *new = NULL;

    new = projectile_create((sfFloatRect){ball->pos.x, ball->pos.y, 20, 20},
        (sfVector2f){10 / sin(M_PI / 2) * sin((M_PI / 2) -
        (ball->angle * M_PI / 180)),
        10 / sin(M_PI / 2) * sin(ball->angle * M_PI / 180)},
        proj, projectile_move_line);
    sfRectangleShape_setRotation(new->rect, ball->angle);
    new->hitbox->owner = new;
    new->time.microseconds = 0;
    new->caster = ball->hitbox->owner;
    new->hitbox->on_collision_entered = projectile_collision;
    return new;
}

void use_cast_magic_ball(weapon_t *ball, UNUSED window_t *win)
{
    static sfTexture *proj = NULL;
    entity_t *caster = NULL;

    if (!ball) {
        sfTexture_destroy(proj);
    } else
        proj = sfTexture_createFromFile("assets/items/Magic_ball.png", NULL);
    caster = ball->hitbox->owner;
    if (caster->enemy.spoted) {
        ball->activated = false;
        instantiate_magic_ball(ball, proj);
    }
}

weapon_t *cast_projectile(int strength)
{
    weapon_t *new = NULL;

    new = malloc(sizeof(weapon_t));
    ASSERT_MALLOC(new, NULL);
    new->activated = true;
    new->angle = 0.;
    new->cooldown = 0;
    new->strenght = strength;
    new->weapon = rectangle_quick_create((sfFloatRect){0, 0, 0, 0},
                                        NULL, sfWhite);
    ASSERT_MALLOC(new->weapon, NULL;)
    new->rect = sfRectangleShape_getGlobalBounds(new->weapon);
    new->hitbox = collider_create(&new->rect, HITBOX, true, new);
    ASSERT_MALLOC(new->hitbox, NULL);
    new->pos = (sfVector2f){0, 0};
    new->use = use_cast_magic_ball;
    return new;
}
