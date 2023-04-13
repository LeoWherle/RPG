/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** gui_setter
*/

#include "SFML/Graphics.h"
#include "errorhandling.h"
#include "gui.h"

static void center_origin(sfRectangleShape *rect, sfVector2f size,
sfVector2f pos)
{
    sfRectangleShape_setOrigin(rect, (sfVector2f){size.x / 2, size.y / 2});
    sfRectangleShape_setPosition(rect, (sfVector2f){pos.x + size.x / 2,
pos.y + size.y / 2});
}

/**
 * @brief creates a rectangle from size and pos
 *
 * @param self the gui to set the RectangleShape
 * @param size the size, width and height of the rectangle
 * @param pos the position of the rectangle
 * @param center 1 to center origin 0 top right origin
 * @return gui_t* return NULL on create error
 */
gui_t *gui_set_rect(gui_t *self, sfVector2f size, sfVector2f pos,
int do_center_origin)
{
    self->shape = sfRectangleShape_create();
    ASSERT_MALLOC(self->shape, NULL);
    sfRectangleShape_setSize(self->shape, size);
    sfRectangleShape_setPosition(self->shape, pos);
    if (do_center_origin)
        center_origin(self->shape, size, pos);
    return self;
}
