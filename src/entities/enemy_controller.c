/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** Enemy controller
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "item.h"
#include "entities.h"

void enemy_update(void *enemy_void, window_t *window)
{
    entity_t *enemy = (entity_t *)enemy_void;

    enemy_move(enemy, window);
    enemy->hitbox = sfSprite_getGlobalBounds(enemy->sprite);
}

void enemy_print(void *enemy_void, window_t *window)
{
    entity_t *enemy = (entity_t *)enemy_void;

    sfSprite_setPosition(enemy->sprite, enemy->pos);
    sfRenderWindow_drawSprite(window->window, enemy->sprite, NULL);
}

void enemy_animation(void *enemy_void, window_t *window)
{
    entity_t *enemy = (entity_t *)enemy_void;

    move_enemy_sprite(enemy, window);
}
