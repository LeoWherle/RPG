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
#include "weapon.h"

void player_update(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    move_player(player, window);
    if (player->knockback)
        player_knockback(player, window);
    check_dir(player);
    player->pos.x += player->speed_vector.x;
    player->pos.y += player->speed_vector.y;
    player->hitbox = get_player_bounds(player);
    collision_check(player->hurt);
    weapon_use(player->weapon, window);
    player_dash_bar(player);
    update_camera(player, window);
}

void player_print(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    sfSprite_setPosition(player->sprite, player->pos);
    if (player->weapon->activated)
        sfRenderWindow_drawRectangleShape(window->window,
        player->weapon->weapon, NULL);
    if (player->got_hit == 1)
        invicibility_frames(player, window);
    else
        sfRenderWindow_drawSprite(window->window, player->sprite, NULL);
    if (player->dash.dash_cooldown > 0)
        sfRenderWindow_drawRectangleShape(window->window,
        player->info_bar, NULL);
    if (player->stats.hp <= 0)
        window->exit = true;
}

void player_animation(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    dash_animation(player);
    animation_controller(player);
    move_player_sprite(player, window);
}
