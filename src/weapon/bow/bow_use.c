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

projectile_t *instantiate_arrow(weapon_t *bow, sfTexture *proj, bool *sent)
{
    projectile_t *new = NULL;

    new = projectile_create((sfFloatRect){bow->pos.x, bow->pos.y, 40, 20},
        (sfVector2f){10 / sin(M_PI / 2) * sin((M_PI / 2) -
        (bow->angle * M_PI / 180)),
        10 / sin(M_PI / 2) * sin(bow->angle * M_PI / 180)},
        proj, projectile_move_line);
    sfRectangleShape_setRotation(new->rect, bow->angle);
    new->hitbox->owner = bow->hitbox->owner;
    *sent = false;
    return new;
}

void bow_use(weapon_t *bow, window_t *window)
{
    static sfTexture *proj = NULL;
    static sfTime prev_time = {0};
    static bool go = true;
    sfTime time = {0};

    if (!bow) {
        sfTexture_destroy(proj);
        return;
    } else if (!proj)
        proj = sfTexture_createFromFile("assets/items/arrow.png", NULL);
    if (prev_time.microseconds == 0)
        prev_time = sfClock_getElapsedTime(window->frame);
    time = sfClock_getElapsedTime(window->frame);
    if ((time.microseconds - prev_time.microseconds) / 1000000. > 0.1 && go)
        instantiate_arrow(bow, proj, &go);
    if ((time.microseconds - prev_time.microseconds) / 1000000. > 0.5) {
        go = true;
        bow->activated = false;
        prev_time.microseconds = 0;
    }
}
