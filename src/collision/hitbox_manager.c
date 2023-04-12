/*
** EPITECH PROJECT, 2023
** Enter hurtbox
** File description:
** RPG
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "item.h"
#include "entities.h"
#include "collision.h"

void on_hurtbox_enter(collider_t *main, collider_t *sub)
{
    entity_t *player = main->owner;
    entity_t *enemy = NULL;

    if (sub->type == HURTBOX && !player->got_hit) {
        enemy = sub->owner;
        player->stats.hp -= enemy->stats.atk;
        player->got_hit = true;
    }
}