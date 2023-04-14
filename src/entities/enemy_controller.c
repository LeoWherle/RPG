/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** Enemy controller
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "entities.h"

void enemy_update(void *enemy_void, window_t *window)
{
    entity_t *enemy = (entity_t *)enemy_void;

    enemy_move(enemy, window);
    if (enemy->knockback)
        ennemy_knockback(enemy, window);
    if (enemy->got_hit)
        enemy_invicibilty(enemy, window);
    check_dir(enemy);
    enemy->pos.x += enemy->speed_vector.x;
    enemy->pos.y += enemy->speed_vector.y;
    enemy->hitbox = sfSprite_getGlobalBounds(enemy->sprite);
    collision_check(enemy->hurt);
    if (enemy->weapon->use)
        enemy->weapon->use(enemy->weapon, window);
    enemy_health_bar(enemy);
}

void enemy_print(void *enemy_void, window_t *window)
{
    entity_t *enemy = (entity_t *)enemy_void;

    sfSprite_setPosition(enemy->sprite, enemy->pos);
    sfRenderWindow_drawSprite(window->window, enemy->sprite, NULL);
    if (enemy->stats.hp < enemy->stats.max_hp)
        sfRenderWindow_drawRectangleShape(window->window,
        enemy->info_bar, NULL);
}

void enemy_animation(void *enemy_void, window_t *window)
{
    entity_t *enemy = (entity_t *)enemy_void;

    move_enemy_sprite(enemy, window);
}
