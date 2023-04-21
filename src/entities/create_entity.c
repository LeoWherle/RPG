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
    entity->stats.speed = stats->speed;
    entity->stats.atk_speed = stats->atk_speed;
    entity->stats.exp.current_exp = stats->exp.current_exp;
    entity->stats.exp.exp_cap = 100;
    entity->stats.exp.level = 1;
    entity->stats.exp.mult = 1.;
}

void set_sprite(entity_t *entity, char *path, sfIntRect anim_rect,
                sfVector2f origin)
{
    entity->visu.texture = sfTexture_createFromFile(path, NULL);
    entity->visu.sprite = sfSprite_create();
    entity->visu.anim_rect = anim_rect;
    sfSprite_setOrigin(entity->visu.sprite, origin);
    sfSprite_setTexture(entity->visu.sprite, entity->visu.texture, sfTrue);
    sfSprite_setTextureRect(entity->visu.sprite, entity->visu.anim_rect);
    sfSprite_setPosition(entity->visu.sprite, entity->pos);
    entity->coll.hitbox = sfSprite_getGlobalBounds(entity->visu.sprite);
}

void set_death_sprite(entity_t *entity, char *path, sfIntRect anim_rect,
                    sfVector2f origin)
{
    entity->visu.death_texture = sfTexture_createFromFile(path, NULL);
    entity->visu.death_sprite = sfSprite_create();
    entity->visu.death_anim_rect = anim_rect;
    sfSprite_setOrigin(entity->visu.death_sprite, origin);
    sfSprite_setTexture(entity->visu.death_sprite,
    entity->visu.death_texture, sfTrue);
    sfSprite_setScale(entity->visu.death_sprite, (sfVector2f)
    {2, 2});
    sfSprite_setTextureRect(entity->visu.death_sprite,
    entity->visu.death_anim_rect);
    sfSprite_setPosition(entity->visu.death_sprite, entity->pos);
}

void set_info_bar(entity_t *entity, sfColor color, sfVector2f size,
                sfVector2f pos)
{
    entity->state.info_bar = sfRectangleShape_create();
    sfRectangleShape_setFillColor(entity->state.info_bar, color);
    sfRectangleShape_setOutlineColor(entity->state.info_bar, sfBlack);
    sfRectangleShape_setOutlineThickness(entity->state.info_bar, 2);
    sfRectangleShape_setSize(entity->state.info_bar, size);
    sfRectangleShape_setPosition(entity->state.info_bar, pos);
}
