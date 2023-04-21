/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** boss death camera
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"

void explosion_particles(entity_t *boss)
{
    sfFloatRect rect = {0};

    sfSprite_setTextureRect(boss->visu.death_sprite,
    boss->visu.death_anim_rect);
    boss->visu.death_anim_rect.left += 50;
    if (boss->visu.death_anim_rect.left >= 600) {
        boss->visu.death_anim_rect.left = 0;
        rect = sfSprite_getGlobalBounds(boss->visu.sprite);
        sfVector2f rand_pos = {rand() % (int)rect.width + rect.left,
        rand() % (int)rect.height + rect.top};
        sfSprite_setPosition(boss->visu.death_sprite, rand_pos);
    }
}

void death_camera_controller(window_t *window, entity_t *boss)
{
    if (!boss->cam.got_player) {
        boss->cam.player_pos = sfView_getCenter(window->view);
        boss->cam.camera_pos = sfView_getCenter(window->view);
        boss->cam.got_player = true;
    }
    if (!boss->cam.shake && !boss->cam.backtrack)
        camera_travel(boss, boss->pos);
    if (boss->cam.backtrack) {
        if (camera_travel(boss, boss->cam.player_pos) == 1)
            boss->enemy.is_dead = true;
    }
    if (boss->cam.shake)
        camera_shake(window, boss, 10);
    explosion_particles(boss);
    sfView_setCenter(window->view, boss->cam.camera_pos);
    sfRenderWindow_setView(window->window, window->view);
    window->event->type = -1;
}
