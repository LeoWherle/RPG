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

void create_player_2(map_t *map, entity_t *player)
{
    player->knockback = false;
    player->hitbox = get_player_bounds(player);
    player->hurt = collider_create(&player->hitbox,
    PLAYER_HURTBOX, true, player);
    player->hurt->owner = player;
    player->hurt->on_collision_entered = player_collision;
    player->trigger = collider_create(NULL, TRIGGER, false, player);
    player->trigger->on_collision_entered = move_trigger_enter;
    player->depend = malloc(sizeof(dependency_t));
    player->depend->dependency = map;
    player->depend->next = NULL;
    set_info_bar(player, sfWhite, (sfVector2f){100, 20},
    (sfVector2f){player->pos.x, player->pos.y - 20});
    spawn_point(player, '$');
}

entity_t *create_player(map_t *map)
{
    entity_t *player = malloc(sizeof(entity_t));
    stats_t stats = {100, PLAYER_HP, PLAYER_ATK, PLAYER_DEF, PLAYER_LUCK,
    PLAYER_SPEED, PLAYER_ATK_SPEED, {0}};

    player->weapon = weapon_create_sword(0.5, 5, (sfVector2f){50, 50},
    "assets/items/sword.png");
    player->weapon->hitbox->owner = player;
    player->pos = (sfVector2f){0, 0};
    player->speed_vector = (sfVector2f){0, 0};
    player->dash.is_dashing = 0;
    player->dash.dash_cooldown = 0;
    player->dash.vector_lock = 0;
    player->got_hit = 0;
    set_sprite(player, "assets/characters/player.png",
    (sfIntRect){0, 0, 48, 48}, (sfVector2f){24, 24});
    set_stats(player, &stats);
    create_player_2(map, player);
    return player;
}
