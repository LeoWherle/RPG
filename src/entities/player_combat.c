/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** combat
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "entities.h"
#include "collision.h"

sfFloatRect get_player_bounds(entity_t *player)
{
    sfFloatRect bounds;

    bounds.left = player->pos.x - 15;
    bounds.top = player->pos.y - 5;
    bounds.width = 33;
    bounds.height = 53;
    return bounds;
}

void player_knockback(entity_t *player, window_t *window)
{
    static sfTime time = {0};
    sfTime current = {0};

    if (time.microseconds == 0)
        time = sfClock_getElapsedTime(window->frame);
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - time.microseconds) / 1000000. > 0.2) {
        time.microseconds = 0;
        player->state.knockback = false;
    }
    if (player->state.knockback) {
        player->speed_vector.x = cos(player->state.hit_angle * M_PI / 180) * 8;
        player->speed_vector.y = sin(player->state.hit_angle * M_PI / 180) * 8;
    }
}

void player_dash_bar(entity_t *player)
{
    sfVector2f pos = {player->pos.x - 30, player->pos.y + 70};
    float percent = (float)player->dash.dash_cooldown /
    PLAYER_DASH_COOLDOWN;

    sfRectangleShape_setPosition(player->state.info_bar, pos);
    sfRectangleShape_setSize(player->state.info_bar,
    (sfVector2f){60 * percent, 10});
}

void invicibility_frames(entity_t *player, window_t *window)
{
    static sfTime time_inv = {0};
    static sfTime time_cool = {0};
    static int is_invisible = true;
    sfTime current_inv = {0};
    sfTime current_cool = {0};

    if (time_cool.microseconds == 0)
        time_cool = sfClock_getElapsedTime(window->frame);
    current_inv = sfClock_getElapsedTime(window->frame);
    current_cool = sfClock_getElapsedTime(window->frame);
    if ((current_cool.microseconds - time_cool.microseconds) / 1000000. > 1) {
        time_cool.microseconds = 0;
        player->state.got_hit = false;
    }
    if ((current_inv.microseconds - time_inv.microseconds) / 1000000. > 0.15) {
        time_inv = current_inv;
        is_invisible = !is_invisible;
    }
    if (!is_invisible)
        sfRenderWindow_drawSprite(window->window, player->visu.sprite, NULL);
}
