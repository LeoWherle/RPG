/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** gui_draw_item
*/

#include <SFML/Graphics.h>
#include "gui.h"
#include "errorhandling.h"
#include "item.h"
#include "entities.h"

static void draw_item(weapon_t *item, window_t *screen, sfVector2f pos)
{
    sfVector2f size = {0, 0};
    sfVector2f origin = {0, 0};
    float rotation = 0;
    sfVector2f normalized_pos = {0, 0};

    ASSERT_MALLOC(item->weapon, );
    size = sfRectangleShape_getSize(item->weapon);
    sfRectangleShape_setSize(item->weapon, (sfVector2f){70, 70});
    normalized_pos = (sfVector2f){(70 / 2) - 10, (70 / 2) - 10};
    origin = sfRectangleShape_getOrigin(item->weapon);
    sfRectangleShape_setOrigin(item ->weapon, normalized_pos);
    rotation = sfRectangleShape_getRotation(item->weapon);
    sfRectangleShape_setRotation(item->weapon, 0);
    sfRectangleShape_setPosition(item->weapon, pos);
    sfRenderWindow_drawRectangleShape(screen->window, item->weapon, NULL);
    sfRectangleShape_setSize(item->weapon, size);
    sfRectangleShape_setOrigin(item->weapon, origin);
    sfRectangleShape_setRotation(item->weapon, rotation);
    sfRectangleShape_setFillColor(item->weapon, sfWhite);
}

static void shade_selected_weapon(inventory_t *inv, weapon_t *item)
{
    sfRectangleShape_setFillColor(inv->weapon->weapon, sfWhite);
    if (inv->weapon == item)
        sfRectangleShape_setFillColor(inv->weapon->weapon,
        sfColor_fromRGB(120, 120, 120));
}

void draw_inventory_items(gui_t *gui, window_t *screen)
{
    inventory_t *inv = (inventory_t *)((entity_t *)gui->interactor)->inventory;
    node_t *slot_element;
    gui_t *slot = NULL;
    weapon_t *item = NULL;
    sfVector2f pos = {0, 0};

    slot_element = gui->sub_gui_list->head;
    for (node_t *node = inv->items->head; node != NULL;
        node = node->next) {
        item = (weapon_t *)node->data;
        slot = (gui_t *)slot_element->data;
        ASSERT_MALLOC(slot,)
        ASSERT_MALLOC(item,)
        pos = sfRectangleShape_getPosition(slot->shape);
        pos.y += 35;
        pos.x += 35;
        slot_element = slot_element->next;
        shade_selected_weapon(inv, item);
        draw_item(item, screen, pos);
    }
}
