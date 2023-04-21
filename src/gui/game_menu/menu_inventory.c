/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_inventory
*/

#include <stdlib.h>
#include "gui.h"
#include "errorhandling.h"
#include "entities.h"
#include "my_str.h"

// return 0 or 1 on error
static inventory_slot_t *inv_slot_init(gui_t *inventory)
{
    inventory_slot_t *new = NULL;
    entity_t *player = (entity_t *)inventory->interactor;
    static int slot_id = 0;

    if ((new = malloc(sizeof(inventory_slot_t))) != NULL) {
        new->slot_id = slot_id++;
        new->inventory = player->inventory;
        return new;
    }
    return new;
}

static void equip_item(void *data, UNUSED window_t *screen)
{
    gui_t *self = (gui_t *)data;
    inventory_slot_t *slot = (inventory_slot_t *)self->interactor;
    inventory_t *inventory = slot->inventory;
    node_t *node = NULL;

    node = node_get(inventory->items, slot->slot_id);
    ASSERT_POINTER(node, );
    inventory->weapon = (weapon_t *)node->data;
}

static void inv_slot_create(gui_t *slot, gui_t *inventory)
{
    sfRectangleShape_setScale(slot->shape, (sfVector2f){2, 2});
    slot->interactor = inv_slot_init(inventory);
    slot->interaction = &equip_item;
}

static gui_t *create_inventory_slots(gui_t *inventory, sfVector2f rposf,
window_t *screen)
{
    gui_t *slot = NULL;
    sfVector2f rpos = sfView_getSize(screen->view);
    int a = 0;
    int b = 0;

    rposf.x /= -1080 * 2;
    rposf.y /= -1920 * 2;
    rpos = (sfVector2f){INV_SPACING / rpos.x, INV_SPACING / rpos.y};
    for (float width = rposf.x; a++ < INV_HEIGHT; width += rpos.y) {
        for (float height = rposf.y; b++ < INV_WIDTH; height += rpos.x) {
            slot = gui_sub_create((sfVector2f){height, width},
"assets/menu/slot.png", inventory);
            ASSERT_MALLOC(slot, NULL);
            inv_slot_create(slot, inventory);
        }
        b = 0;
    }
    return inventory;
}

gui_t *menu_create_inventory(gui_t *gobal_menu, window_t *screen,
                            item_t *player_item)
{
    gui_t *inventory = NULL;
    gui_t *inventory_hud = NULL;

    inventory = gui_sub_create((sfVector2f){0, 0}, NULL, gobal_menu);
    ASSERT_POINTER(inventory, NULL);
    inventory->type = GUI_INVENTORY;
    inventory_hud = gui_sub_create((sfVector2f){0, 0}, NULL, inventory);
    sfRectangleShape_setSize(inventory_hud->shape, (sfVector2f){1920, 1080});
    sfRectangleShape_setFillColor(inventory_hud->shape, SHADOW_COLOR);
    SWAP_VISIBILITY(inventory_hud->state);
    inventory_hud->type = GUI_INV_DISPLAY;
    inventory_hud->interactor = player_item->item;
    ASSERT_POINTER(create_inventory_slots(inventory_hud, INV_POS, screen),
                    NULL);
    inventory_hud = create_stats(inventory_hud, screen);
    ASSERT_POINTER(inventory_hud, NULL);
    inventory_hud->interactor = player_item->item;
    return inventory;
}
