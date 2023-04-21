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
#include "music_player.h"
#include "room.h"
#include "save.h"
#include "projectile.h"

void reset_player(entity_t *player)
{
    player->stats.atk = PLAYER_ATK;
    player->stats.atk_speed = PLAYER_ATK_SPEED;
    player->stats.exp.current_exp = 0;
    player->stats.exp.level = 1;
    player->stats.exp.mult = 1;
    player->stats.exp.exp_cap = PLAYER_EXP_CAP;
    player->stats.max_hp = PLAYER_HP;
    player->stats.hp = player->stats.max_hp;
    player->stats.speed = PLAYER_SPEED;
    player->speed_vector = (sfVector2f){0, 0};
    player->dash.is_dashing = 0;
    player->dash.dash_cooldown = 0;
    player->dash.vector_lock = 0;
    player->state.got_hit = 0;
    player->state.knockback = 0;
}

void reset_scene(entity_t *player, window_t *window)
{
    map_t *map = player->depend->dependency;

    if (!init_map(HOUSE_R, map) || !spawn_enemies(map)) {
        window->state = EXIT_ERROR;
        return;
    }
    clear_projectile_list(NULL);
    spawn_point(player, '$');
    inventory_clear(player->inventory);
    player->coll.weapon = weapon_create_sword(0.5, 30, (sfVector2f){50, 50},
        "assets/items/sword/crystal_sword.png");
    node_append(player->inventory->items, player->coll.weapon);
    player->inventory->weapon = player->coll.weapon;
    if (!player->inventory || !player->coll.weapon) {
        window->state = EXIT_ERROR;
        return;
    }
    player->coll.weapon->hitbox->owner = player;
    reset_player(player);
}

void player_update(void *player_void, window_t *window, float delta)
{
    entity_t *player = (entity_t *)player_void;

    if (player->stats.hp <= 0) {
        reset_scene(player, window);
        window->state = TITLE_SCREEN;
        return;
    }
    move_player(player, window, delta);
    if (player->state.knockback)
        player_knockback(player, window);
    check_dir(player, delta);
    player->pos.x += player->speed_vector.x;
    player->pos.y += player->speed_vector.y;
    player->coll.hitbox = get_player_bounds(player);
    collision_check(player->coll.hurt);
    player->coll.weapon = player->inventory->weapon;
    weapon_use(player->coll.weapon, window, delta);
    player_dash_bar(player);
    update_camera(player, window);
}

void player_print(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    sfSprite_setPosition(player->visu.sprite, player->pos);
    if (player->coll.weapon->hitbox->activated)
        sfRenderWindow_drawRectangleShape(window->window,
        player->coll.weapon->weapon, NULL);
    if (player->state.got_hit == 1)
        invicibility_frames(player, window);
    else
        sfRenderWindow_drawSprite(window->window, player->visu.sprite, NULL);
    if (player->dash.dash_cooldown > 0)
        sfRenderWindow_drawRectangleShape(window->window,
        player->state.info_bar, NULL);
}

void player_animation(void *player_void, window_t *window)
{
    entity_t *player = (entity_t *)player_void;

    dash_animation(player);
    animation_controller(player);
    move_player_sprite(player, window);
}
