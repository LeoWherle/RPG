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

void enemy_health_bar(entity_t *enemy)
{
    sfVector2f pos = {enemy->pos.x - enemy->sprite_size * 2,
    enemy->pos.y + enemy->sprite_size + 50};
    float percent = enemy->stats.hp / enemy->stats.max_hp;

    sfRectangleShape_setPosition(enemy->info_bar, pos);
    sfRectangleShape_setSize(enemy->info_bar, (sfVector2f){80 * percent, 10});
}

void enemy_invicibilty(entity_t *enemy, window_t *window)
{
    static sfTime time = {0};
    sfTime current = {0};

    if (enemy->got_hit)
        sfSprite_setColor(enemy->sprite, sfRed);
    if (time.microseconds == 0)
        time = sfClock_getElapsedTime(window->frame);
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - time.microseconds) / 1000000. > 0.2) {
        time.microseconds = 0;
        enemy->got_hit = false;
        sfSprite_setColor(enemy->sprite, sfWhite);
    }
}
