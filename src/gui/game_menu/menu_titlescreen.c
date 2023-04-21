/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_titlescreen
*/

#include "gui.h"
#include "menu_values.h"
#include "music_player.h"

void title_screen_update(void *gui_void, window_t *game, UNUSED float dt)
{
    node_t *node = NULL;
    gui_t *gui = (gui_t *)gui_void;

    if (gui == NULL)
        return;
    sfRenderWindow_pollEvent(game->window, game->event);
    if (gui_state_is(INVISIBLE | DISABLED, gui->state))
        return;
    if (gui->sub_gui_list != NULL) {
        for (node = gui->sub_gui_list->head; node != NULL; node = node->next) {
            title_screen_update(node->data, game, 0);
        }
    }
    update_one(gui, game);
    return;
}

gui_t *menu_create_titlescreen(UNUSED window_t *window, gui_t *title_screen)
{
    gui_t *backgroud = NULL;

    backgroud = gui_sub_create(GUIPOS_BACKGROUND, BACKGRN, title_screen);
    ASSERT_POINTER(backgroud, NULL);
    sfRectangleShape_setScale(backgroud->shape, (sfVector2f){0.65, 0.65});
    backgroud->state = DISABLED;
    backgroud = menu_create_titlescrn_btn(title_screen, window);
    return title_screen;
}
