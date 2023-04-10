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

void move_enemy_sprite(entity_t *enemy, window_t *window)
{
    static sfTime time = {0};
    sfTime current = {0};

    sfSprite_setTextureRect(enemy->sprite, enemy->anim_rect);
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
    float angle = atan2(target.y - enemy->pos.y, target.x - enemy->pos.x);

    enemy->speed_vector.x = cos(angle) * enemy->stats.speed;
    enemy->speed_vector.y = sin(angle) * enemy->stats.speed;
    check_dir(enemy);
    enemy->pos.x += enemy->speed_vector.x;
    enemy->pos.y += enemy->speed_vector.y;
}
