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

void set_stats(entity_t *player)
{
    player->stats.hp = BASE_HP;
    player->stats.atk = BASE_ATK;
    player->stats.def = BASE_DEF;
    player->stats.luck = BASE_LUCK;
    player->stats.speed = BASE_SPEED;
    player->stats.atk_speed = BASE_ATK_SPEED;
}

entity_t *create_player(window_t *window)
{
    entity_t *player = malloc(sizeof(entity_t));

    player->type = PLAYER_E;
    player->animation = FRONT_IDLE;
    player->texture = sfTexture_createFromFile
    ("assets/characters/player.png", NULL);
    player->sprite = sfSprite_create();
    player->anim_clock = sfClock_create();
    player->pos = (sfVector2f){window->mode.width / 2,
    window->mode.height / 2};
    player->anim_rect = (sfIntRect){0, 0, 48, 48};
    set_stats(player);
    sfSprite_setOrigin(player->sprite, (sfVector2f){24, 24});
    sfSprite_setScale(player->sprite, (sfVector2f){PLAYER_SIZE, PLAYER_SIZE});
    sfSprite_setTexture(player->sprite, player->texture, sfTrue);
    sfSprite_setTextureRect(player->sprite, player->anim_rect);
    sfSprite_setPosition(player->sprite, player->pos);
    set_camera(player, window);
    return player;
}
