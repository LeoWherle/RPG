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
#include "collision.h"

void set_stats(entity_t *entity, stats_t *stats)
{
    entity->stats.hp = stats->hp;
    entity->stats.atk = stats->atk;
    entity->stats.def = stats->def;
    entity->stats.luck = stats->luck;
    entity->stats.speed = stats->speed;
    entity->stats.atk_speed = stats->atk_speed;
}

void set_sprite(entity_t *entity, char *path, sfIntRect anim_rect,
                sfVector2f origin)
{
    entity->texture = sfTexture_createFromFile(path, NULL);
    entity->sprite = sfSprite_create();
    entity->anim_rect = anim_rect;
    sfSprite_setOrigin(entity->sprite, origin);
    sfSprite_setScale(entity->sprite, (sfVector2f){PLAYER_SIZE, PLAYER_SIZE});
    sfSprite_setTexture(entity->sprite, entity->texture, sfTrue);
    sfSprite_setTextureRect(entity->sprite, entity->anim_rect);
    sfSprite_setPosition(entity->sprite, entity->pos);
}

entity_t *create_player(window_t *window)
{
    entity_t *player = malloc(sizeof(entity_t));
    stats_t stats = {PLAYER_HP, PLAYER_ATK, PLAYER_DEF, PLAYER_LUCK,
    PLAYER_SPEED, PLAYER_ATK_SPEED};

    player->dash = malloc(sizeof(player_dash_t));
    player->animation = FRONT_IDLE;
    player->dash->is_dashing = 0;
    player->dash->dash_cooldown = 0;
    player->dash->vector_lock = 0;
    player->sprite_size = 48;
    player->pos = (sfVector2f){window->mode.width / 2,
    window->mode.height / 2};
    set_sprite(player, "assets/characters/player.png",
    (sfIntRect){0, 0, 48, 48}, (sfVector2f){24, 24});
    set_stats(player, &stats);
    player->hurt = collider_create(NULL, HURTBOX, true, player);
    player->trig = (sfFloatRect){0, 0, 1, 1};
    player->trigger = collider_create(&player->trig, TRIGGER, false, player);
    set_camera(player, window);
    return player;
}

entity_t *create_slime(window_t *window)
{
    entity_t *slime = malloc(sizeof(entity_t));
    stats_t stats = {100, 10, 0, 0, 2, 0};

    slime->animation = FRONT_IDLE;
    slime->pos = (sfVector2f){window->mode.width / 2,
    window->mode.height / 2};
    slime->sprite_size = 20;
    set_sprite(slime, "assets/characters/Slime.png",
    (sfIntRect){0, 0, slime->sprite_size, slime->sprite_size},
    (sfVector2f){10, 0});
    set_stats(slime, &stats);
    slime->hurt = collider_create(NULL, HURTBOX, true, slime);
    slime->trig = (sfFloatRect){0, 0, 1, 1};
    slime->trigger = collider_create(&slime->trig, TRIGGER, false, slime);
    return slime;
}
