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

void receive_enemy_damage(collider_t *main, collider_t *sub)
{
    entity_t *player = main->owner;
    entity_t *enemy = NULL;

    if (sub->type == HITBOX && !player->got_hit) {
        enemy = sub->owner;
        player->stats.hp -= enemy->stats.atk;
        player->got_hit = true;
        player->knockback = true;
        player->hit_angle = atan2(player->pos.y - enemy->pos.y,
        player->pos.x - enemy->pos.x) * 180 / M_PI;
    }
}

void receive_player_damage(collider_t *main, collider_t *sub)
{
    entity_t *enemy = main->owner;
    entity_t *player = NULL;

    if (sub->type == PLAYER_HITBOX && !enemy->got_hit) {
        player = sub->owner;
        enemy->stats.hp -= player->stats.atk;
        enemy->got_hit = true;
        enemy->knockback = true;
        enemy->hit_angle = atan2(main->hitbox->top - sub->hitbox->top,
        main->hitbox->left - sub->hitbox->left) * 180 / M_PI;
    }
}
