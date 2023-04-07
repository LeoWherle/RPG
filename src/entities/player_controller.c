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
    player->collider->hitbox->left = player->pos.x - 24;
    player->collider->hitbox->top = player->pos.y - 24;
    collision_check(player->collider, SOLID);
}

void player_update(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    //player_hitbox(player);
    move_player(player, window);
    update_camera(player, window);
}

void player_print(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    sfSprite_setPosition(player->sprite, player->pos);
    sfRenderWindow_drawSprite(window->window, player->sprite, NULL);
}

void player_anim(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    dash_animation(player);
    animation_controller(player);
    player_animation(player, window);
}
