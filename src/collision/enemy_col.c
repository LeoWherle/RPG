/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** enemy col
*/

#include <stdbool.h>
#include "collision.h"
#include "entities.h"

bool receive_player_damage(collider_t *main, collider_t *sub)
{
    entity_t *enemy = main->owner;
    entity_t *player = NULL;

    if (sub->type == PLAYER_HITBOX && !enemy->state.got_hit) {
        player = sub->owner;
        enemy->stats.hp -= player->stats.atk + player->coll.weapon->strenght;
        if (player->coll.weapon->use == sword_use) {
            enemy->state.knockback = true;
        }
        if (enemy->stats.hp <= 0)
            add_exp(&player->stats, enemy->stats.exp.current_exp);
        enemy->enemy.spoted = true;
        enemy->state.got_hit = true;
        enemy->state.hit_angle = atan2(main->hitbox->top - sub->hitbox->top,
        main->hitbox->left - sub->hitbox->left) * 180 / M_PI;
        return true;
    }
    return false;
}

bool receive_player_damage_boss(collider_t *main, collider_t *sub)
{
    entity_t *enemy = main->owner;
    entity_t *player = NULL;

    if (sub->type == PLAYER_HITBOX && !enemy->state.got_hit
    && !enemy->enemy.king_slime.is_jumping) {
        player = sub->owner;
        enemy->stats.hp -= player->stats.atk;
        if (enemy->stats.hp <= 0) {
            player->quest = true;
            add_exp(&player->stats, 300);
        }
        enemy->state.got_hit = true;
        return true;
    }
    return false;
}
