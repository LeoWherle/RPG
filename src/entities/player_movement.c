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

void player_dash(entity_t *player, window_t *window, float delta)
{
    if (player->dash.dash_cooldown <= 0 && player->dash.is_dashing == 1) {
        if (player->dash.vector_lock == 0) {
            player->dash.vector_lock = true;
            player->dash.dash_start = sfClock_getElapsedTime(window->frame);
            player->dash.dash_vector = player->speed_vector;
        }
        player->dash.dash_time = sfClock_getElapsedTime(window->frame);
        if (player->dash.dash_time.microseconds / 1000000.0 -
        player->dash.dash_start.microseconds / 1000000.0 > 0.2) {
            player->dash.is_dashing = true;
            player->dash.dash_cooldown = PLAYER_DASH_COOLDOWN;
            player->dash.vector_lock = false;
        }
        player->speed_vector.x = player->dash.dash_vector.x * 3;
        player->speed_vector.y = player->dash.dash_vector.y * 3;
    } else {
        player->dash.dash_cooldown -= delta * 2.5;
        player->dash.is_dashing = false;
    }
}

void player_orientation(entity_t *player, window_t *window)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);
    sfVector2f absolute_pos = sfRenderWindow_mapPixelToCoords(window->window,
    mouse_pos, window->view);
    float angle = atan2(absolute_pos.y - player->pos.y,
    absolute_pos.x - player->pos.x) * 180 / M_PI;
    player->coll.weapon->angle = angle;
    if (angle < 0)
        angle += 360;
    if (angle > 45 && angle < 135)
        player->visu.animation = FRONT_IDLE;
    if (angle > 225 && angle < 315)
        player->visu.animation = BACK_IDLE;
    if (angle >= 315 || angle <= 45) {
        player->visu.animation = SIDE_IDLE;
        player->visu.facing_right = true;
    }
    if (angle >= 135 && angle <= 225) {
        player->visu.animation = SIDE_IDLE;
        player->visu.facing_right = false;
    }
}

static void reduce_player_speed(entity_t *player)
{
    if (!player->dash.is_dashing && player->coll.weapon->hitbox->activated) {
        player->speed_vector.x /= 2;
        player->speed_vector.y /= 2;
    }
}

void move_player(entity_t *player, window_t *window, float delta)
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
    if (sfKeyboard_isKeyPressed(sfKeyLShift) &&
    (player->speed_vector.x != 0 || player->speed_vector.y != 0))
        player->dash.is_dashing = 1;
    reduce_player_speed(player);
    if (player->speed_vector.x != 0 && player->speed_vector.y != 0) {
        player->speed_vector.x *= SQRT;
        player->speed_vector.y *= SQRT;
    }
    player_orientation(player, window);
    player_dash(player, window, delta);
}
