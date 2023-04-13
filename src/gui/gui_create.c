/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_create
*/

#include <unistd.h>
#include <stdlib.h>
#include "gui.h"
#include "item.h"
#include "errorhandling.h"

/**
 * @brief initialize a gui_t struct
 *
 * @return gui_t* on success, NULL on failure
 */
gui_t *gui_init(void)
{
    gui_t *new_gui = NULL;

    new_gui = malloc(sizeof(gui_t));
    ASSERT_MALLOC(new_gui, NULL);
    new_gui->state = 0;
    new_gui->type = GUI_BASIC;
    new_gui->shape = NULL;
    new_gui->text = NULL;
    new_gui->font = NULL;
    new_gui->sub_gui_list = NULL;
    new_gui->texture = NULL;
    new_gui->interaction = NULL;
    new_gui->rel_pos = (sfVector2f){0, 0};
    return new_gui;
}

gui_t *gui_set_texture(gui_t *gui, char *texture)
{
    sfVector2u texture_size = {0, 0};
    sfVector2f rect_size = {0, 0};

    if (texture != NULL) {
        gui->texture = sfTexture_createFromFile(texture, NULL);
        ASSERT_MALLOC(gui->texture, NULL);
        texture_size = sfTexture_getSize(gui->texture);
        rect_size = (sfVector2f){texture_size.x * 2, texture_size.y * 2};
        sfRectangleShape_setTexture(gui->shape, gui->texture, sfTrue);
    } else {
        sfRectangleShape_setFillColor(gui->shape, sfTransparent);
    }
    sfRectangleShape_setSize(gui->shape, rect_size);
    return gui;
}

gui_t *gui_create(sfVector2f rel_pos, char *texture)
{
    gui_t *new_gui = NULL;

    new_gui = gui_init();
    new_gui->rel_pos = rel_pos;
    ASSERT_MALLOC(new_gui, NULL);
    new_gui->shape = sfRectangleShape_create();
    ASSERT_MALLOC(new_gui->shape, NULL);
    new_gui = gui_set_texture(new_gui, texture);
    ASSERT_POINTER(new_gui, NULL);
    sfRectangleShape_setPosition(new_gui->shape, (sfVector2f){0, 0});
    return new_gui;
}

gui_t *gui_sub_create(sfVector2f rel_pos, char *texture, gui_t *parent)
{
    gui_t *new_gui = NULL;

    new_gui = gui_create(rel_pos, texture);
    ASSERT_POINTER(new_gui, NULL);
    if (parent->sub_gui_list == NULL)
        parent->sub_gui_list = list_init();
    ASSERT_POINTER(parent->sub_gui_list, NULL);
    node_append(parent->sub_gui_list, new_gui);
    return new_gui;
}

/**
 * @brief destroy a gui_t struct
 *
 * @param gui_t takes a void * to be able to use it with list_destroy
 * or item_list_destroy
 */
void gui_destroy(void *gui_any)
{
    gui_t *gui = (gui_t *)gui_any;

    if (gui->shape != NULL)
        sfRectangleShape_destroy(gui->shape);
    if (gui->text != NULL)
        sfText_destroy(gui->text);
    if (gui->font != NULL)
        sfFont_destroy(gui->font);
    if (gui->texture != NULL)
        sfTexture_destroy(gui->texture);
    if (gui->sub_gui_list != NULL)
        list_destroy(gui->sub_gui_list, gui_destroy);
    free(gui);
}
