/*
** EPITECH PROJECT, 2023
** My_RPG
** File description:
** create_player
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "item.h"
#include "entities.h"

void set_stats(entity_t *entity, stats_t *stats)
{
    entity->stats.hp = stats->hp;
    entity->stats.atk = stats->atk;
    entity->stats.def = stats->def;
    entity->stats.luck = stats->luck;
    entity->stats.speed = stats->speed;
    entity->stats.atk_speed = stats->atk_speed;
}

entity_t *create_player(window_t *window)
{
    entity_t *player = malloc(sizeof(entity_t));
    stats_t stats = {PLAYER_HP, PLAYER_ATK, PLAYER_DEF, PLAYER_LUCK,
    PLAYER_SPEED, PLAYER_ATK_SPEED};
    player->type = PLAYER_E;
    player->animation = FRONT_IDLE;
    player->texture = sfTexture_createFromFile
    ("assets/characters/player.png", NULL);
    player->sprite = sfSprite_create();
    player->anim_clock = sfClock_create();
    player->pos = (sfVector2f){window->mode.width / 2,
    window->mode.height / 2};
    player->anim_rect = (sfIntRect){0, 0, 48, 48};
    set_stats(player, &stats);
    sfSprite_setOrigin(player->sprite, (sfVector2f){24, 24});
    sfSprite_setScale(player->sprite, (sfVector2f){PLAYER_SIZE, PLAYER_SIZE});
    sfSprite_setTexture(player->sprite, player->texture, sfTrue);
    sfSprite_setTextureRect(player->sprite, player->anim_rect);
    sfSprite_setPosition(player->sprite, player->pos);
    set_camera(player, window);
    return player;
}
