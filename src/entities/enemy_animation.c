/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** enemy animation
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"

void move_enemy_sprite(entity_t *enemy, window_t *window)
{
    sfTime current = {0};

    if (enemy->visu.facing_right)
        sfSprite_setScale(enemy->visu.sprite, enemy->enemy.scale);
    else
        sfSprite_setScale(enemy->visu.sprite, (sfVector2f)
        {-enemy->enemy.scale.x, enemy->enemy.scale.y});
    sfSprite_setTextureRect(enemy->visu.sprite, enemy->visu.anim_rect);
    current = sfClock_getElapsedTime(window->frame);
    if (current.microseconds / 1000000. -
    enemy->enemy.anim_time.microseconds / 1000000. >
    enemy->enemy.anim_inter) {
        enemy->enemy.anim_time = current;
        enemy->visu.anim_rect.left += enemy->visu.sprite_size;
    }
    if (enemy->visu.anim_rect.left >= enemy->visu.sprite_size *
    enemy->enemy.anim_frames)
        enemy->visu.anim_rect.left = 0;
}
