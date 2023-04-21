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

    collider_destroy(player->coll.hurt);
    collider_destroy(player->coll.trigger);
    inventory_destroy(player->inventory);
    sfSprite_destroy(player->visu.sprite);
    sfTexture_destroy(player->visu.texture);
    sfRectangleShape_destroy(player->state.info_bar);
    free(player->depend);
}

void destroy_enemy(void *enemy_void)
{
    entity_t *enemy = (entity_t *)enemy_void;

    collider_destroy(enemy->coll.hurt);
    collider_destroy(enemy->coll.trigger);
    weapon_destroy(enemy->coll.weapon);
    sfSprite_destroy(enemy->visu.sprite);
    sfTexture_destroy(enemy->visu.texture);
    sfSprite_destroy(enemy->visu.death_sprite);
    sfTexture_destroy(enemy->visu.death_texture);
    sfRectangleShape_destroy(enemy->state.info_bar);
}
