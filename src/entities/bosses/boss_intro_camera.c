/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** Camera effects
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"

void shaking_interval(window_t *window, entity_t *boss, int offset)
{
    static int shake = 0;
    static sfTime shake_interval = {0};
    sfTime current_shake = {0};

    if (shake == 0)
        shake = offset;
    if (shake_interval.microseconds == 0)
        shake_interval = sfClock_getElapsedTime(window->frame);
    current_shake = sfClock_getElapsedTime(window->frame);
    if ((current_shake.microseconds - shake_interval.microseconds)
    / 1000000. > 0.05) {
        shake_interval.microseconds = 0;
        shake = -shake;
        boss->cam.camera_pos.x += shake;
    }
}

void camera_shake(window_t *window, entity_t *boss, int offset)
{
    sfTime current = {0};

    if (boss->cam.shake_time.microseconds == 0)
        boss->cam.shake_time = sfClock_getElapsedTime(window->frame);
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - boss->cam.shake_time.microseconds)
    / 1000000. > 2) {
        boss->cam.shake = false;
        boss->cam.backtrack = true;
    }
    shaking_interval(window, boss, offset);
}

void reset_values(entity_t *boss)
{
    boss->cam.got_player = false;
    boss->cam.cam_lock = false;
    boss->cam.shake = false;
    boss->cam.backtrack = false;
    boss->cam.shake_time.microseconds = 0;
}

int camera_travel(entity_t *boss, sfVector2f target)
{
    sfVector2f cam_speed = {0, 0};
    float angle = 0;

    angle = atan2(target.y - boss->cam.camera_pos.y,
    target.x - boss->cam.camera_pos.x);
    cam_speed.x = cos(angle) * 12;
    cam_speed.y = sin(angle) * 12;
    boss->cam.camera_pos.x += cam_speed.x;
    boss->cam.camera_pos.y += cam_speed.y;
    if (boss->cam.camera_pos.x < target.x + 10 &&
    boss->cam.camera_pos.x > target.x - 10 &&
    boss->cam.camera_pos.y < target.y + 10 &&
    boss->cam.camera_pos.y > target.y - 10) {
        boss->cam.shake = true;
        if (boss->cam.backtrack) {
            reset_values(boss);
            return 1;
        }
    }
    return 0;
}

void camera_controller(window_t *window, entity_t *boss)
{
    if (!boss->cam.got_player) {
        boss->cam.player_pos = sfView_getCenter(window->view);
        boss->cam.camera_pos = sfView_getCenter(window->view);
        boss->cam.got_player = true;
        sfSprite_setPosition(boss->visu.death_sprite, boss->pos);
    }
    if (!boss->cam.shake && !boss->cam.backtrack)
        camera_travel(boss, boss->pos);
    if (boss->cam.backtrack)
        camera_travel(boss, boss->cam.player_pos);
    if (boss->cam.shake)
        camera_shake(window, boss, 10);
    sfView_setCenter(window->view, boss->cam.camera_pos);
    sfRenderWindow_setView(window->window, window->view);
    window->event->type = -1;
}
