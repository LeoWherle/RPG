/*
** EPITECH PROJECT, 2023
** My_RPG
** File description:
** player_controller
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "item.h"
#include "entities.h"
#include "errorhandling.h"

void player_hitbox(entity_t *player)
{
    collider_t *hit_by = NULL;

    player->hurt->hitbox->left = player->pos.x - 24;
    player->hurt->hitbox->top = player->pos.y - 24;
    hit_by = collision_check(player->hurt, HITBOX);
}

void player_update(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    move_player(player, window);
    update_camera(player, window);
}

void player_print(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    sfSprite_setPosition(player->sprite, player->pos);
    sfRenderWindow_drawSprite(window->window, player->sprite, NULL);
}

void player_animation(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    dash_animation(player);
    animation_controller(player);
    move_player_sprite(player, window);
}
