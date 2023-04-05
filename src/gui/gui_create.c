/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_create
*/

#include <unistd.h>
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
    new_gui->shape = NULL;
    new_gui->text = NULL;
    new_gui->font = NULL;
    new_gui->interactors = NULL;
}

gui_t *gui_create_default(void)
{
    gui_t *new_gui = NULL;

    new_gui = gui_init();
    ASSERT_MALLOC(new_gui, NULL);
    new_gui->shape = sfRectangleShape_create();
    ASSERT_MALLOC(new_gui->shape, NULL);
    sfRectangleShape_setSize(new_gui->shape, (sfVector2f){100, 100});
    sfRectangleShape_setPosition(new_gui->shape, (sfVector2f){0, 0});
    sfRectangleShape_setFillColor(new_gui->shape, sfBlue);
}

/**
 * @brief destroy a gui_t struct
 *
 * @param gui_any takes a void * to be able to use it with list_destroy
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
    if (gui->interactors != NULL)
        list_destroy(gui->interactors, gui);
    free(gui);
}
