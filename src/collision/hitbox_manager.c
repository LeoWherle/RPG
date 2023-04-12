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

void on_hurtbox_enter(collider_t *main, collider_t *sub)
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
        enemy->hit_angle = atan2(enemy->pos.y - player->pos.y,
        enemy->pos.x - player->pos.x) * 180 / M_PI;
    }
}
