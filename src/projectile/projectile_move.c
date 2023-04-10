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

void projectile_move_line(projectile_t *proj, window_t *win)
{
    static sfTime prev_time = {0};
    sfTime time = {0};

    if (prev_time.microseconds == 0) {
        prev_time = sfClock_getElapsedTime(win->frame);
    } else {
        time = sfClock_getElapsedTime(win->frame);
    }
    if ((time.microseconds - prev_time.microseconds) / 1000000. > 5) {
        node_delete(proj->projectile_list, proj, projectile_delete);
        prev_time = time;
        return;
    }
    proj->pos.x += proj->move_vect.x;
    proj->pos.y += proj->move_vect.y;
    sfRectangleShape_setPosition(proj->rect, proj->pos);
    proj->box = sfRectangleShape_getGlobalBounds(proj->rect);
}

void projectile_move_sinus(projectile_t *proj, window_t *win)
{
    static float angle = 0.;
    static sfVector2f speed_vect = {0};

    if (speed_vect.x == 0 && speed_vect.y == 0) {
        speed_vect.x = proj->move_vect.x;
        speed_vect.y = proj->move_vect.y;
    }
    if (angle < 1.57) {
        proj->move_vect.x = speed_vect.x / sin(M_PI / 2) * sin((M_PI / 2) - angle);
        proj->move_vect.y = speed_vect.y / sin(M_PI / 2) * sin(angle);
    } else {
        proj->move_vect.x = -speed_vect.x / sin(M_PI / 2) * sin((M_PI / 2) - angle);
        proj->move_vect.y = speed_vect.y / sin(M_PI / 2) * sin(angle);
    }
    angle += 0.1;
    if (angle > 3.14)
        angle = 0.;
    projectile_move_line(proj, win);
}

void projectile_move_boing(projectile_t *proj, window_t *win)
{
    static float angle = -1.57;
    static sfVector2f speed_vect = {0};

    if (speed_vect.x == 0 && speed_vect.y == 0) {
        speed_vect.x = proj->move_vect.x;
        speed_vect.y = proj->move_vect.y;
    }
    if (angle < 1.57) {
        proj->move_vect.x = speed_vect.x / sin(M_PI / 2) * sin((M_PI / 2) - angle);
        proj->move_vect.y = speed_vect.y / sin(M_PI / 2) * sin(angle);
    } else {
        proj->move_vect.x = speed_vect.x / sin(M_PI / 2) * sin((M_PI / 2) - angle);
        proj->move_vect.y = speed_vect.y / sin(M_PI / 2) * sin(angle);
    }
    angle += 0.1;
    if (angle > 1.57)
        angle = -1.57;
    projectile_move_line(proj, win);
}