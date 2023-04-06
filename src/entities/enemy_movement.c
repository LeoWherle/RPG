/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** Enemy movement
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "item.h"
#include "entities.h"

void enemy_animation(entity_t *enemy)
{
    enemy->anim_time = sfClock_getElapsedTime(enemy->anim_clock);
    if (enemy->anim_time.microseconds / 1000000.0 > INTERVAL) {
        enemy->anim_rect.left += enemy->sprite_size;
        sfClock_restart(enemy->anim_clock);
    }
    if (enemy->anim_rect.left >= enemy->sprite_size * 5)
        enemy->anim_rect.left = 0;
}

void enemy_move(entity_t *enemy, window_t *window)
{
    sfVector2f target = sfView_getCenter(window->view);

    if (enemy->pos.x < target.x)
        enemy->pos.x += enemy->stats.speed;
    if (enemy->pos.x > target.x)
        enemy->pos.x -= enemy->stats.speed;
    if (enemy->pos.y < target.y)
        enemy->pos.y += enemy->stats.speed;
    if (enemy->pos.y > target.y)
        enemy->pos.y -= enemy->stats.speed;
    sfSprite_setTextureRect(enemy->sprite, enemy->anim_rect);
    enemy_animation(enemy);
}