/*
** EPITECH PROJECT, 2023
** Player_movement
** File description:
** RPG
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <math.h>
#include "item.h"
#include "entities.h"
#include "collision.h"

void player_dash(entity_t *player, window_t *window)
{
    if (player->dash->dash_cooldown <= 0 && player->dash->is_dashing == 1) {
        if (player->dash->vector_lock == 0) {
            player->dash->vector_lock = 1;
            player->dash->dash_start = sfClock_getElapsedTime(window->frame);
            player->dash->dash_vector = player->speed_vector;
        }
        player->dash->dash_time = sfClock_getElapsedTime(window->frame);
        if (player->dash->dash_time.microseconds / 1000000.0 -
        player->dash->dash_start.microseconds / 1000000.0 > 0.2) {
            player->dash->is_dashing = 0;
            player->dash->dash_cooldown = 2;
            player->dash->vector_lock = 0;
        }
        player->speed_vector.x = player->dash->dash_vector.x * 3;
        player->speed_vector.y = player->dash->dash_vector.y * 3;
    } else {
        player->dash->is_dashing = 0;
        player->dash->dash_cooldown -= 0.05;
    }
}

void player_orientation(entity_t *player, window_t *window)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);
    sfVector2f absolute_pos = sfRenderWindow_mapPixelToCoords(window->window,
    mouse_pos, window->view);
    float angle = atan2(absolute_pos.y - player->pos.y,
    absolute_pos.x - player->pos.x) * 180 / M_PI;

    if (angle < 0)
        angle += 360;
    if (angle > 45 && angle < 135)
        player->animation = FRONT_IDLE;
    if (angle > 225 && angle < 315)
        player->animation = BACK_IDLE;
    if (angle >= 315 || angle <= 45) {
        player->animation = SIDE_IDLE;
        player->facing_right = true;
    }
    if (angle >= 135 && angle <= 225) {
        player->animation = SIDE_IDLE;
        player->facing_right = false;
    }
}

void check_dir(entity_t *player)
{
    collider_t *col = NULL;

    player->trig.left = player->pos.x;
    player->trig.top = player->pos.y;
    col = collision_check(player->trigger, SOLID);
    if (col) {
        player->speed_vector.x = 0;
        player->speed_vector.y = 0;
    }
}

void move_player(entity_t *player, window_t *window)
{
    player->speed_vector = (sfVector2f){0, 0};
    if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyUp))
        player->speed_vector.y -= player->stats.speed;
    if (sfKeyboard_isKeyPressed(sfKeyS) || sfKeyboard_isKeyPressed(sfKeyDown))
        player->speed_vector.y += player->stats.speed;
    if (sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyLeft))
        player->speed_vector.x -= player->stats.speed;
    if (sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyRight))
        player->speed_vector.x += player->stats.speed;
    if (sfKeyboard_isKeyPressed(sfKeyLShift))
        player->dash->is_dashing = 1;
    if (player->speed_vector.x != 0 && player->speed_vector.y != 0) {
        player->speed_vector.x *= SQRT;
        player->speed_vector.y *= SQRT;
    }
    player_orientation(player, window);
    player_dash(player, window);
    check_dir(player);
    player->pos.x += player->speed_vector.x;
    player->pos.y += player->speed_vector.y;
}
