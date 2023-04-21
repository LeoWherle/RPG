/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** Create king slime
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"
#include "collision.h"

void set_king_slime_2(entity_t *king_slime)
{
    sfColor shadow_color = {0, 0, 0, 100};
    king_slime->enemy.king_slime.jump_height = 500;
    king_slime->enemy.king_slime.sprite_pos = (sfVector2f){0, 0};
    king_slime->enemy.king_slime.is_jumping = false;
    king_slime->enemy.king_slime.sprite_pos = (sfVector2f){0, 0};
    king_slime->enemy.king_slime.is_jumping = false;
    king_slime->enemy.king_slime.jump_start = false;
    king_slime->enemy.king_slime.shadow = sfCircleShape_create();
    king_slime->enemy.king_slime.timer = 2;
    sfCircleShape_setRadius(king_slime->enemy.king_slime.shadow,
    KING_SLIME_SPRITE_SIZE * 2.5);
    sfCircleShape_setFillColor(king_slime->enemy.king_slime.shadow,
    shadow_color);
    sfCircleShape_setOrigin(king_slime->enemy.king_slime.shadow,
    (sfVector2f){KING_SLIME_SPRITE_SIZE * 2.5,
    KING_SLIME_SPRITE_SIZE * 2.5 - 60});
    set_sprite(king_slime, "assets/characters/king_slime.png",
    (sfIntRect){0, 0, KING_SLIME_SPRITE_SIZE, KING_SLIME_SPRITE_SIZE + 10},
    (sfVector2f){KING_SLIME_SPRITE_SIZE / 2, KING_SLIME_SPRITE_SIZE / 2});
    sfSprite_setScale(king_slime->visu.sprite, (sfVector2f){5, 5});
}

void set_king_slime(entity_t *boss)
{
    boss->enemy.is_boss = true;
    boss->state.got_hit = false;
    boss->enemy.anim_frames = 8;
    boss->enemy.is_dead = false;
    boss->coll.hurt = collider_create(&boss->coll.hitbox, HURTBOX, true, boss);
    boss->coll.hurt->owner = boss;
    boss->coll.hurt->on_collision_entered = receive_player_damage_boss;
    boss->coll.trigger = collider_create(NULL, TRIGGER, false, boss);
    boss->coll.trigger->on_collision_entered = move_trigger_enter;
    boss->enemy.invi_time = sfTime_Zero;
    boss->enemy.death_time = sfTime_Zero;
    boss->coll.weapon = body_damage((sfVector2f){KING_SLIME_SPRITE_SIZE * 3,
    KING_SLIME_SPRITE_SIZE * 3}, boss->stats.atk);
    boss->coll.weapon->hitbox->owner = boss;
    set_info_bar(boss, sfRed, (sfVector2f){100, 20},
    (sfVector2f){boss->pos.x, boss->pos.y - 20});
    set_death_sprite(boss, "assets/characters/death.png",
    (sfIntRect){0, 0, 50, 50}, (sfVector2f){25, 25});
}

entity_t *create_king_slime(sfVector2f pos)
{
    entity_t *king_slime = malloc(sizeof(entity_t));
    stats_t stats = {1000, 1000, 40, 4.5, 0, {0}};
    king_slime->pos = pos;
    king_slime->enemy.king_slime.offset = 0.;
    king_slime->cam.cam_lock = true;
    king_slime->cam.camera_pos = (sfVector2f){0, 0};
    king_slime->cam.player_pos = (sfVector2f){0, 0};
    king_slime->cam.got_player = false;
    king_slime->cam.shake = false;
    king_slime->cam.backtrack = false;
    king_slime->cam.shake_time = sfTime_Zero;
    king_slime->cam.pass_update = false;
    king_slime->enemy.king_slime.jump_delay = sfTime_Zero;
    king_slime->enemy.king_slime.jump_speed = 0;
    king_slime->visu.sprite_size = KING_SLIME_SPRITE_SIZE;
    set_king_slime_2(king_slime);
    sfSprite_setScale(king_slime->visu.sprite, (sfVector2f){5, 5});
    set_stats(king_slime, &stats);
    set_king_slime(king_slime);
    return king_slime;
}
