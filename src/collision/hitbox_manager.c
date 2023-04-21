/*
** EPITECH PROJECT, 2023
** Enter hurtbox
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
#include "weapon.h"
#include "room.h"
#include "music_player.h"
#include "projectile.h"

bool receive_enemy_damage(collider_t *main, collider_t *sub)
{
    entity_t *player = main->owner;
    entity_t *enemy = NULL;

    if (sub->type == HITBOX && !player->state.got_hit) {
        enemy = sub->owner;
        if (!player->dash.is_dashing) {
            player->stats.hp -= enemy->stats.atk;
            player->state.got_hit = true ;
            player->state.knockback = true;
        }
        player->state.hit_angle = atan2(player->pos.y - enemy->pos.y,
        player->pos.x - enemy->pos.x) * 180 / M_PI;
        return true;
    }
    return false;
}

static void set_music(tag_t old)
{
    if (old == TELEPORTER_VILLAGE || old == TELEPORTER_ROOM) {
        change_music(NULL, VILLAGE_M);
    }
    if (old == TELEPORTER_CAVE) {
        change_music(NULL, NORMAL_FIGHT_M);
    }
    if (old == TELEPORTER_BOSS) {
        change_music(NULL, BOSS_FIGHT_M);
    }
}

bool teleporter_trigger(collider_t *main, collider_t *sub)
{
    entity_t *player = main->owner;
    map_t *map = player->depend->dependency;
    window_t *window = player->depend->next->dependency;
    tag_t old = sub->type;

    sfRenderWindow_clear(window->window, sfBlack);
    sfRenderWindow_display(window->window);
    set_music(old);
    if (!init_map(old - TELEPORTER_VILLAGE, map) || !spawn_enemies(map)) {
        window->state = EXIT_ERROR;
        return true;
    }
    clear_projectile_list(NULL);
    if (old == TELEPORTER_VILLAGE) {
        spawn_point(player, '@');
    }
    if (old > TELEPORTER_VILLAGE)
        spawn_point(player, '$');
    return true;
}

bool interact_collision(collider_t *player, collider_t *sub)
{
    void (* interact)(entity_t *, collider_t *) = NULL;
    entity_t *owner = NULL;

    if (sub->type == INTERACTION && sfKeyboard_isKeyPressed(sfKeySpace)) {
        owner = player->owner;
        interact = sub->owner;
        interact(owner, sub);
        return true;
    }
    return false;
}

bool player_collision(collider_t *player, collider_t *sub)
{
    if (receive_enemy_damage(player, sub))
        return true;
    if (sub->type >= TELEPORTER_VILLAGE)
        return teleporter_trigger(player, sub);
    if (interact_collision(player, sub))
        return true;
    return false;
}
