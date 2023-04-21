/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** gui_draw
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "gui.h"
#include "errorhandling.h"
#include "item.h"
#include "entities.h"
#include "my_str.h"

static void set_relative_pos(gui_t *gui, window_t *screen)
{
    sfVector2f hudsize;
    sfVector2f viewsize;
    sfVector2f viewcenter;
    float hudx = 0;
    float hudy = 0;

    hudsize = sfRectangleShape_getSize(gui->shape);
    viewsize = sfView_getSize(screen->view);
    viewcenter = sfView_getCenter(screen->view);
    hudx = viewcenter.x + (viewsize.x * gui->rel_pos.x) - (hudsize.x / 2);
    hudy = viewcenter.y + (viewsize.y * gui->rel_pos.y) - (hudsize.y / 2);
    sfRectangleShape_setPosition(gui->shape, (sfVector2f){hudx, hudy});
    if (gui->text != NULL) {
        sfText_setPosition(gui->text, (sfVector2f){hudx, hudy});
    }
}

static void change_shade(gui_t *gui)
{
    sfUint8 color_shade = 255;
    sfColor color = sfWhite;

    if (gui->texture != NULL) {
        color_shade = 255 - (gui_state_is(gui->state, PRESSED) +
                            gui_state_is(gui->state, HOVER)) * 60;
        color = sfColor_fromRGB(color_shade, color_shade, color_shade);
        sfRectangleShape_setFillColor(gui->shape, color);
    }
}

static void draw_stats(entity_t *player, sfText *text)
{
    weapon_t *weapon = player->inventory->weapon;
    char *stats = malloc(sizeof(char) * 100);

    ASSERT_MALLOC(stats,);
    my_strcpy(stats, "\tStats\n\nLevel:");
    my_strcat(stats, nbr_to_str(player->stats.exp.level));
    my_strcat(stats, "\n\nMax HP:");
    my_strcat(stats, nbr_to_str(player->stats.max_hp));
    my_strcat(stats, "\n\nAttack:");
    my_strcat(stats, nbr_to_str(player->stats.atk));
    my_strcat(stats, "\n\nSpeed:");
    my_strcat(stats, nbr_to_str(player->stats.speed));
    my_strcat(stats, "\n\n\tWeapon\n\nStrength:");
    my_strcat(stats, nbr_to_str(weapon->strenght));
    my_strcat(stats, "\n\nAttack Speed:");
    my_strcat(stats, nbr_to_str(player->stats.atk_speed / weapon->cooldown));
    sfText_setString(text, stats);
    free(stats);
}

void gui_draw_one(void *gui_item, window_t *screen)
{
    gui_t *gui = (gui_t *)gui_item;
    sfVector2f rpos = {0, 0};
    if (gui->shape == NULL)
        return;
    set_relative_pos(gui, screen);
    if (gui->type == GUI_HEALTH_BAR)
        edit_health_bar(gui);
    if (gui->type == GUI_EXP_BAR)
        edit_exp_bar(gui);
    change_shade(gui);
    sfRenderWindow_drawRectangleShape(screen->window, gui->shape, NULL);
    if (gui->text != NULL) {
        if (gui->type == GUI_INV_STATS) {
            rpos = sfRectangleShape_getPosition(gui->shape);
            sfText_setPosition(gui->text, (sfVector2f){rpos.x - 45,
            rpos.y - 50});
            draw_stats(gui->interactor, gui->text);
        }
        sfRenderWindow_drawText(screen->window, gui->text, NULL);
    }
}

void gui_draw(void *gui_item, window_t *screen)
{
    gui_t *gui = (gui_t *)gui_item;
    node_t *node = NULL;

    if (gui == NULL)
        return;
    if (gui_state_is(INVISIBLE, gui->state))
        return;
    gui_draw_one(gui, screen);
    if (gui->sub_gui_list == NULL)
        return;
    for (node = gui->sub_gui_list->head; node != NULL; node = node->next)
        gui_draw(node->data, screen);
    if (gui->type == GUI_INV_DISPLAY)
        draw_inventory_items(gui, screen);
    return;
}
