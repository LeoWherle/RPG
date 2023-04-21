/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_option_text
*/

#include "gui.h"
#include "menu_values.h"
#include "my_str.h"

gui_t *menu_create_opt_tt_buttons(gui_t *option_hud, UNUSED window_t *screen)
{
    gui_t *fonctionnality = NULL;
    gui_t *background = NULL;

    background = gui_sub_create((sfVector2f){0, 0}, NULL, option_hud);
    sfRectangleShape_setSize(background->shape, (sfVector2f){1920, 1080});
    sfRectangleShape_setFillColor(background->shape, SHADOW_COLOR);
    fonctionnality = create_option_volume(option_hud);
    ASSERT_POINTER(fonctionnality, NULL)
    fonctionnality = create_option_fullscreen(option_hud);
    ASSERT_POINTER(fonctionnality, NULL)
    fonctionnality = create_option_winsize(option_hud);
    ASSERT_POINTER(fonctionnality, NULL)
    fonctionnality = create_option_tutorial(option_hud);
    ASSERT_POINTER(fonctionnality, NULL)
    return option_hud;
}

void open_menu(void *gui, UNUSED window_t *screen)
{
    gui_t *self = (gui_t *)gui;

    if (self->type == GUI_OPTIONS) {
        SWAP_VISIBILITY(((gui_t *)(self->sub_gui_list->head->data))->state);
    }
}

gui_t *create_option_text(gui_t *inventory, char *str, sfVector2f pos)
{
    gui_t *slot = NULL;

    slot = gui_sub_create(pos, NULL, inventory);
    ASSERT_POINTER(slot, NULL);
    slot->font = sfFont_createFromFile("assets/font/Monocraft.otf");
    ASSERT_MALLOC(slot->font, NULL);
    slot->text = sfText_create();
    ASSERT_MALLOC(slot->text, NULL);
    sfText_setString(slot->text, str);
    sfText_setFont(slot->text, slot->font);
    sfText_setCharacterSize(slot->text, 50);
    sfText_setOutlineColor(slot->text, sfBlack);
    sfText_setOutlineThickness(slot->text, 5);
    ASSERT_MALLOC(slot, NULL);
    return slot;
}
