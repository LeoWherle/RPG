/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** use function for bow
*/

#include <math.h>
#include <SFML/Graphics.h>
#include "weapon.h"
#include "projectile.h"
#include "item.h"

projectile_t *instantiate_arrow(weapon_t *bow, sfTexture *proj, bool *sent,
                                window_t *window)
{
    projectile_t *new = NULL;

    new = projectile_create((sfFloatRect){bow->pos.x, bow->pos.y, 40, 20},
        (sfVector2f){10 / sin(M_PI / 2) * sin((M_PI / 2) -
        (bow->angle * M_PI / 180)),
        10 / sin(M_PI / 2) * sin(bow->angle * M_PI / 180)},
        proj, projectile_move_line);
    if (!proj || !new) {
        window->state = EXIT_ERROR;
        return NULL;
    }
    new->move_vect.x /= (1. / 60.);
    new->move_vect.y /= (1. / 60.);
    sfRectangleShape_setRotation(new->rect, bow->angle);
    new->hitbox->owner = new;
    new->time.microseconds = 0;
    new->caster = bow->hitbox->owner;
    new->hitbox->on_collision_entered = projectile_collision;
    *sent = false;
    return new;
}

sfTime set_timing(float *cast, weapon_t *bow, window_t *window)
{
    *cast = bow->cooldown / 5.;
    return sfClock_getElapsedTime(window->frame);
}

void bow_use(weapon_t *bow, window_t *window, UNUSED float delta)
{
    static sfTexture *proj = NULL;
    static sfTime p_time = {0};
    static bool go = true;
    static float cast = 0.;
    sfTime time = {0};
    if (!bow) {
        if (proj) sfTexture_destroy(proj);
        proj = NULL;
        return;
    } else if (!proj)
        proj = sfTexture_createFromFile("assets/items/arrow.png", NULL);
    if (p_time.microseconds == 0) p_time = set_timing(&cast, bow, window);
    time = sfClock_getElapsedTime(window->frame);
    if ((time.microseconds - p_time.microseconds) / 1000000. > cast && go)
        instantiate_arrow(bow, proj, &go, window);
    if ((time.microseconds - p_time.microseconds) / 1000000. > cast * 4) {
        go = true;
        bow->hitbox->activated = false;
        p_time.microseconds = 0;
    }
}
