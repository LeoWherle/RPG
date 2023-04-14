/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** Destry entity
*/

#include <stdlib.h>
#include "weapon.h"
#include "entities.h"

void destroy_player(void *player_void)
{
    entity_t *player = (entity_t *)player_void;

    collider_destroy(player->hurt);
    collider_destroy(player->trigger);
    weapon_destroy(player->weapon);
    sfSprite_destroy(player->sprite);
    sfTexture_destroy(player->texture);
    sfRectangleShape_destroy(player->info_bar);
    free(player->depend);
}

void destroy_enemy(void *enemy_void)
{
    entity_t *enemy = (entity_t *)enemy_void;

    collider_destroy(enemy->hurt);
    collider_destroy(enemy->trigger);
    weapon_destroy(enemy->weapon);
    sfSprite_destroy(enemy->sprite);
    sfTexture_destroy(enemy->texture);
    sfRectangleShape_destroy(enemy->info_bar);
}
