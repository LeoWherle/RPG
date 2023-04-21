/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** create enemies
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"

entity_t *create_ice_ghost(sfVector2f pos)
{
    entity_t *entity = malloc(sizeof(entity_t));
    stats_t stats = {200, 200, 20, 1.5, 1.5, {0, 60, 0, 0}};

    entity->pos = pos;
    entity->visu.sprite_size = ICE_GHOST_SPRITE_SIZE;
    entity->enemy.anim_inter = 0.3;
    entity->enemy.scale = (sfVector2f){3, 3};
    set_sprite(entity, "assets/characters/ice_ghost.png",
    (sfIntRect){0, 0, ICE_GHOST_SPRITE_SIZE, 36},
    (sfVector2f){13, 0});
    sfSprite_setScale(entity->visu.sprite, entity->enemy.scale);
    set_enemy(entity, 300, LONG_RANGE, 8);
    set_enemy_2(entity, &stats, cast_projectile);
    return entity;
}

entity_t *create_skull(sfVector2f pos)
{
    entity_t *entity = malloc(sizeof(entity_t));
    stats_t stats = {300, 300, 15, 2.3, 1, {0, 70, 0, 0}};

    entity->pos = pos;
    entity->visu.sprite_size = 24;
    entity->enemy.anim_inter = 0.2;
    entity->enemy.scale = (sfVector2f){3, 3};
    set_sprite(entity, "assets/characters/skull.png",
    (sfIntRect){0, 0, 25, 40},
    (sfVector2f){13, 20});
    sfSprite_setScale(entity->visu.sprite, entity->enemy.scale);
    set_enemy(entity, 300, LONG_RANGE, 5);
    set_enemy_2(entity, &stats, cast_projectile);
    return entity;
}

entity_t *create_demon(sfVector2f pos)
{
    entity_t *entity = malloc(sizeof(entity_t));
    stats_t stats = {300, 300, 20, 3, 0, {0, 80, 0, 0}};

    entity->pos = pos;
    entity->visu.sprite_size = 21;
    entity->enemy.anim_inter = 0.1;
    entity->enemy.scale = (sfVector2f){4, 4};
    set_sprite(entity, "assets/characters/demon.png",
    (sfIntRect){0, 0, 21, 15},
    (sfVector2f){11, 0});
    sfSprite_setScale(entity->visu.sprite, entity->enemy.scale);
    set_enemy(entity, 300, CLOSE_RANGE, 6);
    set_enemy_2(entity, &stats, body_damage);
    return entity;
}

entity_t *create_little_skeleton(sfVector2f pos)
{
    entity_t *entity = malloc(sizeof(entity_t));
    stats_t stats = {240, 240, 13, 2, 0, {0, 50, 0, 0}};

    entity->pos = pos;
    entity->visu.sprite_size = 14;
    entity->enemy.anim_inter = 0.1;
    entity->enemy.scale = (sfVector2f){3, 3};
    set_sprite(entity, "assets/characters/lil_skel.png",
    (sfIntRect){0, 0, 14, 20},
    (sfVector2f){7, 0});
    sfSprite_setScale(entity->visu.sprite, entity->enemy.scale);
    set_enemy(entity, 300, CLOSE_RANGE, 6);
    set_enemy_2(entity, &stats, body_damage);
    return entity;
}

entity_t *create_big_skeleton(sfVector2f pos)
{
    entity_t *entity = malloc(sizeof(entity_t));
    stats_t stats = {500, 500, 25, 2.5, 0, {0, 100, 0, 0}};

    entity->pos = pos;
    entity->visu.sprite_size = 22;
    entity->enemy.anim_inter = 0.1;
    entity->enemy.scale = (sfVector2f){4, 4};
    set_sprite(entity, "assets/characters/big_skel.png",
    (sfIntRect){0, 0, 22, 28},
    (sfVector2f){11, 10});
    sfSprite_setScale(entity->visu.sprite, entity->enemy.scale);
    set_enemy(entity, 300, CLOSE_RANGE, 8);
    set_enemy_2(entity, &stats, body_damage);
    return entity;
}
