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

void enemy_update(void *enemy_void, window_t *window, float delta)
{
    entity_t *enemy = (entity_t *)enemy_void;

    if (enemy->visu.death_anim_rect.left > 0) {
        enemy->coll.weapon->hitbox->activated = false;
        return;
    }
    enemy_move(enemy, window);
    if (enemy->state.knockback)
        ennemy_knockback(enemy, window);
    if (enemy->state.got_hit)
        enemy_invicibilty(enemy, window);
    check_dir(enemy, delta);
    enemy->pos.x += enemy->speed_vector.x;
    enemy->pos.y += enemy->speed_vector.y;
    enemy->coll.hitbox = sfSprite_getGlobalBounds(enemy->visu.sprite);
    collision_check(enemy->coll.hurt);
    if (enemy->coll.weapon->use)
        enemy->coll.weapon->use(enemy->coll.weapon, window, delta);
    enemy_health_bar(enemy, 80);
}

void enemy_print(void *enemy_void, window_t *window)
{
    entity_t *enemy = (entity_t *)enemy_void;

    sfSprite_setPosition(enemy->visu.sprite, enemy->pos);
    sfSprite_setPosition(enemy->visu.death_sprite, enemy->pos);
    if (enemy->stats.hp < enemy->stats.max_hp && enemy->stats.hp > 0)
        sfRenderWindow_drawRectangleShape(window->window,
        enemy->state.info_bar, NULL);
    if (enemy->visu.death_anim_rect.left > 0)
        sfRenderWindow_drawSprite(window->window,
        enemy->visu.death_sprite, NULL);
    else
        sfRenderWindow_drawSprite(window->window, enemy->visu.sprite, NULL);
}

void enemy_animation(void *enemy_void, window_t *window)
{
    entity_t *enemy = (entity_t *)enemy_void;

    move_enemy_sprite(enemy, window);
}
