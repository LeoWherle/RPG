/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** Enemy movement
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <math.h>
#include "item.h"
#include "entities.h"

void move_enemy_sprite(entity_t *enemy, window_t *window)
{
    sfTime current = {0};

    sfSprite_setTextureRect(enemy->sprite, enemy->anim_rect);
    current = sfClock_getElapsedTime(window->frame);
    if (current.microseconds / 1000000. -
    enemy->enemy.anim_time.microseconds / 1000000. > INTERVAL) {
        enemy->enemy.anim_time = current;
        enemy->anim_rect.left += enemy->sprite_size;
    }
    if (enemy->anim_rect.left >= enemy->sprite_size * 5)
        enemy->anim_rect.left = 0;
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
        enemy->knockback = false;
    }
    if (enemy->knockback) {
        enemy->speed_vector.x = cos(enemy->hit_angle * M_PI / 180) * 8;
        enemy->speed_vector.y = sin(enemy->hit_angle * M_PI / 180) * 8;
    }
}

void enemy_vector(entity_t *enemy, float angle, float speed)
{
    enemy->speed_vector.x = cos(angle) * speed;
    enemy->speed_vector.y = sin(angle) * speed;
}

void enemy_wander(entity_t *enemy, window_t *window)
{
    sfTime current = {0};

    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - enemy->enemy.wander_time.microseconds)
    / 1000000. > 2) {
        enemy->enemy.wander_time = current;
        if (enemy->enemy.is_moving == 0) {
            enemy->enemy.rand_angle = rand() % 360;
            enemy->enemy.is_moving = 1;
        } else
            enemy->enemy.is_moving = 0;
    }
    if (enemy->enemy.is_moving == 1) {
        enemy_vector(enemy, enemy->enemy.rand_angle, enemy->stats.speed / 2);
    }
}

void enemy_move(entity_t *enemy, window_t *window)
{
    sfVector2f target = sfView_getCenter(window->view);
    int range = enemy->enemy.range;
    float angle = atan2(target.y - enemy->pos.y, target.x - enemy->pos.x);
    float distance_from_center = sqrt(pow(target.x - enemy->pos.x, 2) +
    pow(target.y - enemy->pos.y, 2));

    if (enemy->enemy.spoted == 1)
        range = enemy->enemy.range * 2;
    else
        range = enemy->enemy.range;
    if (distance_from_center > range) {
        enemy_wander(enemy, window);
        enemy->enemy.spoted = 0;
        return;
    }
    enemy->enemy.spoted = 1;
    if (distance_from_center < enemy->enemy.proj_range)
        enemy_vector(enemy, angle + 180, enemy->stats.speed);
    else if (distance_from_center > enemy->enemy.proj_range + 50)
        enemy_vector(enemy, angle, enemy->stats.speed);
}
