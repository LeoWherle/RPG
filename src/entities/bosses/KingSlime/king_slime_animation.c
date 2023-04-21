/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** King slime animation
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "entities.h"

void move_animation(entity_t *slime, window_t *window)
{
    static sfTime time;
    sfTime current;

    if (time.microseconds == 0)
        time = sfClock_getElapsedTime(window->frame);
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - time.microseconds) / 1000000. > 0.1) {
        slime->visu.anim_rect.left += KING_SLIME_SPRITE_SIZE;
        time.microseconds = 0;
    }
    if (slime->visu.anim_rect.left >= KING_SLIME_SPRITE_SIZE *
    slime->enemy.anim_frames)
        slime->visu.anim_rect.left = 0;
}

void king_slime_anim_controller(entity_t *slime, window_t *window)
{
    sfSprite_setTextureRect(slime->visu.sprite, slime->visu.anim_rect);
    if (slime->enemy.king_slime.is_jumping)
        slime->visu.anim_rect.left = KING_SLIME_SPRITE_SIZE * 7;
    if (!slime->enemy.king_slime.is_jumping)
        move_animation(slime, window);
}
