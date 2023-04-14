/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** Create_slime
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"
#include "collision.h"

void create_slime_2(entity_t *slime)
{
    slime->enemy.anim_frames = 5;
    slime->weapon = body_damage((sfVector2f){SLIME_SPRITE_SIZE * 3,
    SLIME_SPRITE_SIZE * 3},
    slime->stats.atk);
    slime->weapon->hitbox->owner = slime;
    slime->got_hit = false;
    slime->knockback = false;
    slime->hitbox = sfSprite_getGlobalBounds(slime->sprite);
    slime->hurt = collider_create(&slime->hitbox, HURTBOX, true, slime);
    slime->hurt->owner = slime;
    slime->hurt->on_collision_entered = receive_player_damage;
    slime->trigger = collider_create(NULL, TRIGGER, false, slime);
    slime->trigger->on_collision_entered = move_trigger_enter;
    set_info_bar(slime, sfRed, (sfVector2f){100, 20},
    (sfVector2f){slime->pos.x, slime->pos.y - 20});
}

entity_t *create_slime(sfVector2f pos)
{
    entity_t *slime = malloc(sizeof(entity_t));
    stats_t stats = {100, 100, 10, 0, 0, 2, 0, {0}};

    slime->pos = pos;
    slime->sprite_size = SLIME_SPRITE_SIZE;
    slime->enemy.range = 300;
    slime->enemy.proj_range = CLOSE_RANGE;
    slime->enemy.spoted = 0;
    slime->enemy.rand_angle = 0;
    slime->enemy.is_moving = 0;
    slime->enemy.knock_time = (sfTime){0};
    slime->enemy.wander_time = (sfTime){0};
    slime->enemy.anim_time = (sfTime){0};
    slime->speed_vector = (sfVector2f){0, 0};
    set_sprite(slime, "assets/characters/Slime.png",
    (sfIntRect){0, 0, SLIME_SPRITE_SIZE, SLIME_SPRITE_SIZE},
    (sfVector2f){10, 0});
    set_stats(slime, &stats);
    create_slime_2(slime);
    return slime;
}
