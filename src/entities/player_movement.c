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

void player_animation(entity_t *player)
{
    player->anim_time = sfClock_getElapsedTime(player->anim_clock);
    if (player->anim_time.microseconds / 1000000.0 > INTERVAL) {
        player->anim_rect.left += 48;
        sfClock_restart(player->anim_clock);
    }
    if (player->anim_rect.left >= 288)
        player->anim_rect.left = 0;
}

void animation_controller(entity_t *player, sfVector2f speed_vector)
{
    if (speed_vector.x != 0 || speed_vector.y != 0) {
        if (player->animation == FRONT_IDLE)
            player->animation = FRONT_WALK;
        if (player->animation == BACK_IDLE)
            player->animation = BACK_WALK;
        if (player->animation == SIDE_IDLE)
            player->animation = SIDE_WALK;
    }
    player->anim_rect.top = player->animation * 48;
    sfSprite_setTextureRect(player->sprite, player->anim_rect);
    if (player->animation == SIDE_IDLE || player->animation == SIDE_WALK) {
        if (player->facing_right)
            sfSprite_setScale(player->sprite,
            (sfVector2f){PLAYER_SIZE, PLAYER_SIZE});
        else
            sfSprite_setScale(player->sprite,
            (sfVector2f){-PLAYER_SIZE, PLAYER_SIZE});
    }
    player_animation(player);
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

void move_player(entity_t *player, window_t *window)
{
    sfVector2f speed_vector = {0, 0};

    if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyUp))
        speed_vector.y -= player->stats.speed;
    if (sfKeyboard_isKeyPressed(sfKeyS) || sfKeyboard_isKeyPressed(sfKeyDown))
        speed_vector.y += player->stats.speed;
    if (sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyLeft))
        speed_vector.x -= player->stats.speed;
    if (sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyRight))
        speed_vector.x += player->stats.speed;
    if (speed_vector.x != 0 && speed_vector.y != 0) {
        speed_vector.x *= SQRT;
        speed_vector.y *= SQRT;
    }
    player->pos.x += speed_vector.x;
    player->pos.y += speed_vector.y;
    player_orientation(player, window);
    animation_controller(player, speed_vector);
}
