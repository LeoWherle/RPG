/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** Destry entity
*/

#include "entities.h"

void destroy_player(void *player_void)
{
    entity_t *player = (entity_t *)player_void;

    sfSprite_destroy(player->sprite);
    sfTexture_destroy(player->texture);
}

void destroy_enemy(void *enemy_void)
{
    entity_t *enemy = (entity_t *)enemy_void;

    sfSprite_destroy(enemy->sprite);
    sfTexture_destroy(enemy->texture);
}
