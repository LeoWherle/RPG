/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** gui_draw
*/

#include <SFML/Graphics.h>
#include "gui.h"
#include "errorhandling.h"

void gui_draw(sfRenderWindow *window, gui_t *gui)
{
    sfRenderWindow_drawRectangleShape(window, gui->shape, NULL);
}