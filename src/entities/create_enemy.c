/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** Create_entity
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"
#include "collision.h"

void set_enemy_2(entity_t *entity, stats_t *stats,
            weapon_t *(* create_weapon)(sfVector2f size, int strength))
{
    entity->enemy.is_boss = false;
    entity->visu.facing_right = true;
    entity->speed_vector = (sfVector2f){0, 0};
    entity->state.got_hit = false;
    entity->state.knockback = false;
    set_stats(entity, stats);
    entity->coll.weapon = create_weapon((sfVector2f)
    {entity->visu.sprite_size * 3, entity->visu.sprite_size * 3},
    entity->stats.atk);
    entity->coll.weapon->hitbox->owner = entity;
    set_info_bar(entity, sfRed, (sfVector2f){100, 20},
    (sfVector2f){entity->pos.x, entity->pos.y - entity->visu.sprite_size});
    set_death_sprite(entity, "assets/characters/death.png",
    (sfIntRect){0, 0, 50, 50}, (sfVector2f){25, 25});
}

void set_enemy(entity_t *entity, float range, float proj_range, int frames)
{
    entity->enemy.range = range;
    entity->enemy.proj_range = proj_range;
    entity->enemy.spoted = 0;
    entity->enemy.rand_angle = 0;
    entity->enemy.is_moving = false;
    entity->enemy.anim_frames = frames;
    entity->enemy.is_dead = false;
    entity->coll.hurt = collider_create(&entity->coll.hitbox,
    HURTBOX, true, entity);
    entity->coll.hurt->owner = entity;
    entity->coll.hurt->on_collision_entered = receive_player_damage;
    entity->coll.trigger = collider_create(NULL, TRIGGER, false, entity);
    entity->coll.trigger->on_collision_entered = move_trigger_enter;
    entity->enemy.knock_time = sfTime_Zero;
    entity->enemy.wander_time = sfTime_Zero;
    entity->enemy.anim_time = sfTime_Zero;
    entity->enemy.invi_time = sfTime_Zero;
    entity->enemy.death_time = sfTime_Zero;
    entity->enemy.attack_time = sfTime_Zero;
}

entity_t *create_slime(sfVector2f pos)
{
    entity_t *entity = malloc(sizeof(entity_t));
    stats_t stats = {160, 160, 8, 2, 0, {0, 30, 0, 0}};

    entity->pos = pos;
    entity->visu.sprite_size = SLIME_SPRITE_SIZE;
    entity->enemy.anim_inter = 0.1;
    entity->enemy.scale = (sfVector2f){3, 3};
    set_sprite(entity, "assets/characters/Slime.png",
    (sfIntRect){0, 0, SLIME_SPRITE_SIZE, SLIME_SPRITE_SIZE},
    (sfVector2f){10, 0});
    sfSprite_setScale(entity->visu.sprite, entity->enemy.scale);
    set_enemy(entity, 300, CLOSE_RANGE, 5);
    set_enemy_2(entity, &stats, body_damage);
    return entity;
}
