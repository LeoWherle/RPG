/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** enemy combat
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "entities.h"
#include "quick_create.h"

void enemy_health_bar(entity_t *enemy, int bar_size)
{
    sfVector2f pos = {enemy->coll.hurt->hitbox->left - 10,
    enemy->coll.hurt->hitbox->top + enemy->coll.hurt->hitbox->height + 15};
    float percent = enemy->stats.hp / enemy->stats.max_hp;

    sfRectangleShape_setPosition(enemy->state.info_bar, pos);
    sfRectangleShape_setSize(enemy->state.info_bar,
    (sfVector2f){bar_size * percent, 10});
}

void enemy_explosion(entity_t *enemy, window_t *window)
{
    sfTime current = {0};

    sfSprite_setTextureRect(enemy->visu.death_sprite,
    enemy->visu.death_anim_rect);
    if (enemy->enemy.death_time.microseconds == 0)
        enemy->enemy.death_time = sfClock_getElapsedTime(window->frame);
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - enemy->enemy.death_time.microseconds)
    / 1000000. > 0.01) {
        enemy->enemy.death_time.microseconds = 0;
        enemy->visu.death_anim_rect.left += 50;
    }
    if (enemy->visu.death_anim_rect.left >= 600) {
        enemy->enemy.is_dead = true;
    }
}

void enemy_invicibilty(entity_t *enemy, window_t *window)
{
    sfTime current = {0};

    if (enemy->state.got_hit)
        sfSprite_setColor(enemy->visu.sprite, (sfColor){150, 0, 0, 255});
    if (enemy->enemy.invi_time.microseconds == 0)
        enemy->enemy.invi_time = sfClock_getElapsedTime(window->frame);
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - enemy->enemy.invi_time.microseconds)
    / 1000000. > 0.2) {
        enemy->enemy.invi_time.microseconds = 0;
        enemy->state.got_hit = false;
        sfSprite_setColor(enemy->visu.sprite, sfWhite);
    }
}

void ennemy_knockback(entity_t *enemy, window_t *window)
{
    sfTime current = {0};

    if (enemy->enemy.knock_time.microseconds == 0)
        enemy->enemy.knock_time = sfClock_getElapsedTime(window->frame);
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - enemy->enemy.knock_time.microseconds)
    / 1000000. > 0.2) {
        enemy->enemy.knock_time.microseconds = 0;
        enemy->state.knockback = false;
    }
    if (enemy->state.knockback) {
        enemy->speed_vector.x = cos(enemy->state.hit_angle * M_PI / 180) * 8;
        enemy->speed_vector.y = sin(enemy->state.hit_angle * M_PI / 180) * 8;
    }
}
