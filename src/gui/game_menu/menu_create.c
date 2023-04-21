/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_create
*/

#include <stdlib.h>
#include "menu_values.h"
#include "errorhandling.h"
#include "entities.h"
#include "item.h"

static gui_t *menu_create_bars_background(gui_t *hud)
{
    gui_t *exp_background = NULL;
    gui_t *health_background = NULL;

    exp_background = gui_sub_create(GUIPOS_EXP,
                                    "assets/menu/health_e.png", hud);
    ASSERT_POINTER(exp_background, NULL);
    exp_background->state = DISABLED;
    sfRectangleShape_setScale(exp_background->shape, (sfVector2f){0.7, 0.7});
    health_background = gui_sub_create(GUIPOS_HEALTH,
                                        "assets/menu/health_e.png", hud);
    ASSERT_POINTER(health_background, NULL);
    health_background->state = DISABLED;
    sfRectangleShape_setScale(health_background->shape, (sfVector2f){0.7, 0.7});
    return hud;
}

gui_t *menu_create_hud(gui_t *global_menu, window_t *screen)
{
    gui_t *hud = NULL;
    gui_t *options = NULL;

    hud = gui_sub_create((sfVector2f){1, 1}, NULL, global_menu);
    ASSERT_POINTER(hud, NULL);
    hud->type = GUI_HUD;
    hud = menu_create_bars_background(hud);
    ASSERT_POINTER(hud, NULL);
    options = menu_create_option(global_menu, screen);
    ASSERT_POINTER(options, NULL);
    return hud;
}

gui_t *bars_init(gui_t *hud, item_t *player_item)
{
    gui_t *bar = NULL;
    entity_t *player = (entity_t *)(player_item->item);

    bar = gui_sub_create(GUIPOS_HEALTH, "assets/menu/health_f.png", hud);
    ASSERT_POINTER(bar, NULL);
    bar->type = GUI_HEALTH_BAR;
    bar->interactor = &player->stats;
    bar->state = DISABLED;
    bar = gui_sub_create(GUIPOS_EXP, "assets/menu/exp.png", hud);
    ASSERT_POINTER(bar, NULL);
    bar->type = GUI_EXP_BAR;
    bar->interactor = &player->stats;
    bar->state = DISABLED;
    return bar;
}

gui_t *create_gui(window_t *screen)
{
    gui_t *global = NULL;
    gui_t *sub_menu = NULL;

    global = gui_create((sfVector2f){0, -0.48}, NULL);
    ASSERT_POINTER(global, NULL);
    sub_menu = menu_create_hud(global, screen);
    ASSERT_POINTER(sub_menu, NULL);
    return global;
}

gui_t *create_stats(gui_t *inventory, window_t *screen)
{
    gui_t *slot = NULL;
    sfVector2f rpos = sfView_getSize(screen->view);
    float width = 0;
    float height = 0;

    rpos = (sfVector2f){INV_SPACING / rpos.x, INV_SPACING / rpos.y};
    width = rpos.x + 0.2;
    height = rpos.y - 0.45;
    slot = gui_sub_create((sfVector2f){width, height}, NULL, inventory);
    ASSERT_POINTER(slot, NULL);
    slot->font = sfFont_createFromFile("assets/font/Monocraft.otf");
    ASSERT_MALLOC(slot->font, NULL);
    slot->text = sfText_create(); slot->type = GUI_INV_STATS;
    ASSERT_MALLOC(slot->text, NULL);
    sfText_setFont(slot->text, slot->font);
    sfText_setCharacterSize(slot->text, 50);
    sfText_setOutlineColor(slot->text, sfBlack);
    sfText_setOutlineThickness(slot->text, 5);
    ASSERT_MALLOC(slot, NULL);
    return slot;
}
