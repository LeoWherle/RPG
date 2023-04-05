/*
** EPITECH PROJECT, 2023
** Camera
** File description:
** RPG
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "item.h"
#include "entities.h"

void set_camera(entity_t *player, window_t *window)
{
    sfVector2f size = (sfVector2f){window->mode.width, window->mode.height};

    window->view = sfView_create();
    sfView_setCenter(window->view, player->pos);
    sfView_setSize(window->view, size);
    sfRenderWindow_setView(window->window, window->view);
}

void update_camera(entity_t *player, window_t *window)
{
    sfView_setCenter(window->view, player->pos);
    sfRenderWindow_setView(window->window, window->view);
}
