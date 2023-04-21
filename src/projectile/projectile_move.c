/*
** EPITECH PROJECT, 2023
** my rpg
** File description:
** move function for projectile
*/

#include <SFML/System.h>
#include <math.h>
#include "projectile.h"
#include "item.h"
#include "entities.h"

void projectile_move_line(projectile_t *proj, window_t *win, float delta)
{
    sfTime time = {0};

    if (proj->time.microseconds == 0) {
        proj->time = sfClock_getElapsedTime(win->frame);
    } else {
        time = sfClock_getElapsedTime(win->frame);
    }
    if ((time.microseconds - proj->time.microseconds) / 1000000. > 1.2) {
        node_delete(proj->projectile_list, proj, projectile_delete);
        return;
    }
    proj->pos.x += proj->move_vect.x * delta;
    proj->pos.y += proj->move_vect.y * delta;
    sfRectangleShape_setPosition(proj->rect, proj->pos);
    proj->box = sfRectangleShape_getGlobalBounds(proj->rect);
    collision_check(proj->hitbox);
}

void projectile_move_sinus(projectile_t *proj, window_t *win, float delta)
{
    static float angle = 0.;
    static sfVector2f speed = {0};

    if (speed.x == 0 && speed.y == 0) {
        speed.x = proj->move_vect.x;
        speed.y = proj->move_vect.y;
    }
    if (angle < 1.57) {
        proj->move_vect.x = speed.x / sin(M_PI / 2) * sin((M_PI / 2) - angle);
        proj->move_vect.y = speed.y / sin(M_PI / 2) * sin(angle);
    } else {
        proj->move_vect.x = -speed.x / sin(M_PI / 2) *
                            sin((M_PI / 2) - angle);
        proj->move_vect.y = speed.y / sin(M_PI / 2) * sin(angle);
    }
    angle += 0.1;
    if (angle > 3.14)
        angle = 0.;
    projectile_move_line(proj, win, delta);
}
