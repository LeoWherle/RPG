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

void enemy_speed_vector(entity_t *enemy, float angle, float speed)
{
    enemy->speed_vector.x = cos(angle) * speed;
    enemy->speed_vector.y = sin(angle) * speed;
}

void enemy_behavior(entity_t *enemy, float angle, float dis)
{
    enemy->enemy.spoted = 1;
    if (dis > enemy->enemy.proj_range) {
        enemy_speed_vector(enemy, angle, enemy->stats.speed);
    } else if (dis < enemy->enemy.proj_range + 50) {
        angle += 180;
        enemy_speed_vector(enemy, angle, enemy->stats.speed);
    }
}

void enemy_wander(entity_t *enemy, window_t *window)
{
    sfTime current = {0};
    if (enemy->enemy.wander_time.microseconds == 0)
        enemy->enemy.wander_time = sfClock_getElapsedTime(window->frame);
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - enemy->enemy.wander_time.microseconds)
    / 1000000. > 2) {
        enemy->enemy.wander_time.microseconds = 0;
        if (enemy->enemy.is_moving == 0) {
            enemy->enemy.rand_angle = rand() % 360;
            enemy->enemy.is_moving = 1;
        } else
            enemy->enemy.is_moving = 0;
    } if (enemy->enemy.is_moving == 1) {
        enemy_speed_vector(enemy, enemy->enemy.rand_angle,
        enemy->stats.speed / 2);
        if (enemy->speed_vector.x < 0)
            enemy->visu.facing_right = 0;
        else
            enemy->visu.facing_right = 1;
    }
}

int check_range(entity_t *enemy, float angle)
{
    int range = enemy->enemy.range;

    if (enemy->enemy.spoted == 1) {
        range = enemy->enemy.range * 2;
        if (angle * 180 / M_PI > 90 || angle * 180 / M_PI < -90)
            enemy->visu.facing_right = 0;
        else
            enemy->visu.facing_right = 1;
    } else
        range = enemy->enemy.range;
    return range;
}

void enemy_move(entity_t *enemy, window_t *window)
{
    sfVector2f target = sfView_getCenter(window->view);
    int range = enemy->enemy.range;
    float angle = atan2(target.y - enemy->pos.y, target.x - enemy->pos.x);
    float dis = sqrt(pow(target.x - enemy->pos.x, 2)
    + pow(target.y - enemy->pos.y, 2));

    enemy->speed_vector.x = 0;
    enemy->speed_vector.y = 0;
    enemy->coll.weapon->angle = angle;
    range = check_range(enemy, angle);
    if (dis > range && enemy->stats.hp == enemy->stats.max_hp) {
        enemy_wander(enemy, window);
        enemy->enemy.spoted = 0;
        return;
    }
    enemy_behavior(enemy, angle, dis);
}
