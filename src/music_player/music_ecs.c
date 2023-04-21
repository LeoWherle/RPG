/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** music ecs function
*/

#include <SFML/System.h>
#include <SFML/Graphics.h>
#include "music_player.h"
#include "item.h"
#include "errorhandling.h"

void music_update(void *item, window_t *window, UNUSED float delta)
{
    static sfTime prev_time = {0};
    static bool prev = false;
    sfTime current = sfTime_Zero;
    music_player_t *player = item;
    sfVector2f pos = {0};

    if (player->new && !prev) {
        prev_time = sfClock_getElapsedTime(window->frame);
    }
    prev = player->new;
    current = sfClock_getElapsedTime(window->frame);
    if ((current.microseconds - prev_time.microseconds) / 1000000. < 5.) {
        pos = sfView_getCenter(window->view);
        pos.x -= 860;
        pos.y += 440;
        sfText_setPosition(player->title, pos);
    } else if (player->new)
        player->new = false;
}

void music_print(void *item, window_t *window)
{
    music_player_t *player = item;

    if (player->new) {
        sfRenderWindow_drawText(window->window, player->title, NULL);
    }
}
