/*
** EPITECH PROJECT, 2023
** RG
** File description:
** create player
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"
#include "collision.h"
#include "save.h"

static void create_player_2(map_t *map, entity_t *player, window_t *window)
{
    player->state.knockback = false;
    player->coll.hitbox = get_player_bounds(player);
    player->coll.hurt = collider_create(&player->coll.hitbox,
    PLAYER_HURTBOX, true, player);
    player->coll.hurt->owner = player;
    player->coll.hurt->on_collision_entered = player_collision;
    player->coll.trigger = collider_create(NULL, TRIGGER, false, player);
    player->coll.trigger->on_collision_entered = move_trigger_enter;
    player->depend = malloc(sizeof(dependency_t));
    player->depend->dependency = map;
    player->depend->next = malloc(sizeof(dependency_t));
    player->depend->next->dependency = window;
    player->depend->next->next = NULL;
    set_info_bar(player, sfWhite, (sfVector2f){100, 20},
    (sfVector2f){player->pos.x, player->pos.y - 20});
    spawn_point(player, '$');
}

entity_t *create_player(map_t *map, window_t *window)
{
    entity_t *player = malloc(sizeof(entity_t));
    stats_t stats = {PLAYER_HP, PLAYER_HP, PLAYER_ATK,
    PLAYER_SPEED, PLAYER_ATK_SPEED, {0}};
    player->coll.weapon = weapon_create_sword(0.5, 30, (sfVector2f){50, 50},
        "assets/items/sword/crystal_sword.png");
    ASSERT_MALLOC(player->coll.weapon, NULL);
    player->inventory = inventory_create(player->coll.weapon);
    player->coll.weapon->hitbox->owner = player;
    player->pos = (sfVector2f){0, 0};
    player->speed_vector = (sfVector2f){0, 0};
    player->dash.is_dashing = 0;
    player->dash.dash_cooldown = 0;
    player->dash.vector_lock = 0;
    player->state.got_hit = 0;
    set_sprite(player, "assets/characters/player.png",
    (sfIntRect){0, 0, 48, 48}, (sfVector2f){24, 24});
    sfSprite_setScale(player->visu.sprite, (sfVector2f) {3, 3});
    set_stats(player, &stats);
    create_player_2(map, player, window);
    return player;
}
