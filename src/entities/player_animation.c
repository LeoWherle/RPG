/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** player
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <math.h>
#include "item.h"
#include "entities.h"
#include "collision.h"

void player_animation(entity_t *player, window_t *window)
{
    static sfTime time = {0};
    sfTime current = {0};

    current = sfClock_getElapsedTime(window->frame);
    player->anim_time = sfClock_getElapsedTime(player->anim_clock);
    if (current.microseconds / 1000000 - time.microseconds / 1000000 > INTERVAL) {
        time = current;
        player->anim_rect.left += 48;
        sfClock_restart(player->anim_clock);
    }
    if (player->anim_rect.left >= 288)
        player->anim_rect.left = 0;
}

void dash_animation(entity_t *player)
{
    if (player->dash->is_dashing == 1 && player->dash->dash_cooldown <= 0) {
        if (player->speed_vector.x == 0 && player->speed_vector.y > 0)
            player->animation = FRONT_DASH;
        if (player->speed_vector.x == 0 && player->speed_vector.y < 0)
            player->animation = BACK_DASH;
        if (player->speed_vector.x > 0 || player->speed_vector.x < 0)
            player->animation = SIDE_DASH;
    }
}

void animation_controller(entity_t *player)
{
    if (player->speed_vector.x != 0 || player->speed_vector.y != 0) {
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
}