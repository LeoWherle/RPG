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

void enemy_animation(entity_t *enemy, window_t *window)
{
    static sfTime time = {0};
    sfTime current = {0};

    current = sfClock_getElapsedTime(window->frame);
    if (current.microseconds / 1000000. -
    time.microseconds / 1000000. > INTERVAL) {
        time = current;
        enemy->anim_rect.left += enemy->sprite_size;
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
    enemy_animation(enemy, window);
}
