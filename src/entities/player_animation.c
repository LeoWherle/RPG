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

void move_player_sprite(entity_t *player, window_t *window)
{
    static sfTime time = {0};
    sfTime current = {0};

    current = sfClock_getElapsedTime(window->frame);
    if (player->visu.animation == FRONT_DASH ||
    player->visu.animation == BACK_DASH ||
    player->visu.animation == SIDE_DASH) {
        if (player->visu.animation == SIDE_DASH)
            player->visu.anim_rect.left = 0;
        else
            player->visu.anim_rect.left = PLAYER_SPRITE_SIZE;
    } else if (current.microseconds / 1000000. -
    time.microseconds / 1000000. > 0.1) {
        time = current;
        player->visu.anim_rect.left += PLAYER_SPRITE_SIZE;
    }
    if (player->visu.anim_rect.left >= PLAYER_SPRITE_SIZE * 6)
        player->visu.anim_rect.left = 0;
}

void dash_animation(entity_t *player)
{
    if (player->dash.is_dashing == 1 && player->dash.dash_cooldown <= 0) {
        if (player->speed_vector.x == 0 && player->speed_vector.y > 0)
            player->visu.animation = FRONT_DASH;
        if (player->speed_vector.x == 0 && player->speed_vector.y < 0)
            player->visu.animation = BACK_DASH;
        if (player->speed_vector.x > 0) {
            player->visu.animation = SIDE_DASH;
            player->visu.facing_right = true;
        }
        if (player->speed_vector.x < 0) {
            player->visu.animation = SIDE_DASH;
            player->visu.facing_right = false;
        }
    }
}

void animation_controller(entity_t *player)
{
    if (player->speed_vector.x != 0 || player->speed_vector.y != 0) {
        if (player->visu.animation == FRONT_IDLE)
            player->visu.animation = FRONT_WALK;
        if (player->visu.animation == BACK_IDLE)
            player->visu.animation = BACK_WALK;
        if (player->visu.animation == SIDE_IDLE)
            player->visu.animation = SIDE_WALK;
    }
    player->visu.anim_rect.top = player->visu.animation * PLAYER_SPRITE_SIZE;
    sfSprite_setTextureRect(player->visu.sprite, player->visu.anim_rect);
    if (player->visu.animation == SIDE_IDLE ||
    player->visu.animation == SIDE_WALK
    || player->visu.animation == SIDE_DASH) {
        if (player->visu.facing_right)
            sfSprite_setScale(player->visu.sprite,
            (sfVector2f){PLAYER_SIZE, PLAYER_SIZE});
        else
            sfSprite_setScale(player->visu.sprite,
            (sfVector2f){-PLAYER_SIZE, PLAYER_SIZE});
    }
}
