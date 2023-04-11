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

void enemy_vector(entity_t *enemy, float angle, float speed)
{
    enemy->speed_vector.x = cos(angle) * speed;
    enemy->speed_vector.y = sin(angle) * speed;
    check_dir(enemy);
    enemy->pos.x += enemy->speed_vector.x;
    enemy->pos.y += enemy->speed_vector.y;
}

void enemy_wander(entity_t *enemy, window_t *window)
{
    static int rand_angle = 0;
    static int is_moving = 0;
    static sfTime time = {0};
    sfTime current = {0};

    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - time.microseconds) / 1000000. > 2) {
        time = current;
        if (is_moving == 0) {
            rand_angle = rand() % 360;
            is_moving = 1;
        } else
            is_moving = 0;
    }
    if (is_moving == 1) {
        enemy_vector(enemy, rand_angle, enemy->stats.speed / 2);
    }
}

void enemy_move(entity_t *enemy, window_t *window)
{
    sfVector2f target = sfView_getCenter(window->view);
    int range = enemy->enemy->range;
    float angle = atan2(target.y - enemy->pos.y, target.x - enemy->pos.x);
    float distance_from_center = sqrt(pow(target.x - enemy->pos.x, 2) +
    pow(target.y - enemy->pos.y, 2));

    if (enemy->enemy->spoted == 1)
        range = enemy->enemy->range * 2;
    else
        range = enemy->enemy->range;
    if (distance_from_center > range) {
        enemy_wander(enemy, window);
        enemy->enemy->spoted = 0;
        return;
    }
    enemy->enemy->spoted = 1;
    if (distance_from_center < enemy->enemy->proj_range)
        enemy_vector(enemy, angle + 180, enemy->stats.speed);
    else if (distance_from_center > enemy->enemy->proj_range + 50)
        enemy_vector(enemy, angle, enemy->stats.speed);
}
