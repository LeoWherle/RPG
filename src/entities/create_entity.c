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
#include "weapon.h"
#include "quick_create.h"
#include "room.h"

void set_stats(entity_t *entity, stats_t *stats)
{
    entity->stats.max_hp = stats->max_hp;
    entity->stats.hp = stats->hp;
    entity->stats.atk = stats->atk;
    entity->stats.def = stats->def;
    entity->stats.luck = stats->luck;
    entity->stats.speed = stats->speed;
    entity->stats.atk_speed = stats->atk_speed;
    entity->stats.exp.current_exp = 0;
    entity->stats.exp.exp_cap = 100;
    entity->stats.exp.level = 1;
    entity->stats.exp.mult = 1.;
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

void set_info_bar(entity_t *entity, sfColor color, sfVector2f size,
                sfVector2f pos)
{
    entity->info_bar = sfRectangleShape_create();
    sfRectangleShape_setFillColor(entity->info_bar, color);
    sfRectangleShape_setSize(entity->info_bar, size);
    sfRectangleShape_setPosition(entity->info_bar, pos);
}
