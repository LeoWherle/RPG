/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** King slime movement
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "entities.h"

void king_slime_airtime(entity_t *slime, float delta)
{
    static float x = 0;
    static float max = 0;
    static int speed = 0;
    float fx = 0;

    if (speed == 0) {
        max = sqrt(slime->enemy.king_slime.jump_height);
        x = -max;
        speed = max * 2 / 1;
    }
    x += speed * delta;
    fx = slime->enemy.king_slime.jump_height - pow(x, 2);
    slime->enemy.king_slime.sprite_pos.y = slime->pos.y - fx;
    if (x >= max) {
        slime->enemy.king_slime.is_jumping = false;
        speed = 0;
        max = 0;
        x = 0;
    }
}

void king_slime_jump(entity_t *slime, window_t *window, float delta)
{
    sfTime current = {0};
    if (slime->stats.hp <= slime->stats.max_hp / 2) {
        sfSprite_setColor(slime->visu.sprite, sfRed);
        slime->enemy.king_slime.timer = 1.3;
    }
    slime->enemy.king_slime.sprite_pos.x = slime->pos.x;
    if (!slime->enemy.king_slime.is_jumping)
        slime->enemy.king_slime.sprite_pos = slime->pos;
    if (slime->enemy.king_slime.jump_delay.microseconds == 0)
        slime->enemy.king_slime.jump_delay =
        sfClock_getElapsedTime(window->frame);
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds -
    slime->enemy.king_slime.jump_delay.microseconds)
    / 1000000. > slime->enemy.king_slime.timer) {
        slime->enemy.king_slime.is_jumping = true;
        slime->enemy.king_slime.jump_delay.microseconds = 0;
    }
    if (slime->enemy.king_slime.is_jumping)
        king_slime_airtime(slime, delta);
}

void king_slime_move(entity_t *slime, window_t *window)
{
    sfVector2f target = sfView_getCenter(window->view);
    float angle = atan2(target.y - slime->pos.y, target.x - slime->pos.x);

    if (slime->enemy.king_slime.is_jumping)
        slime->coll.weapon->hitbox->activated = false;
    else {
        slime->coll.weapon->hitbox->activated = true;
        slime->speed_vector.x = cos(angle) * slime->stats.speed;
        slime->speed_vector.y = sin(angle) * slime->stats.speed;
    }
    if (slime->stats.hp <= slime->stats.max_hp / 2) {
        slime->speed_vector.x = cos(angle) * slime->stats.speed;
        slime->speed_vector.y = sin(angle) * slime->stats.speed;
    }
}
