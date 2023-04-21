/*
** EPITECH PROJECT, 2023
** B-MUL-200-TLS-2-1-myrpg-leo.wehrle [WSL: fedora]
** File description:
** inventory
*/

#include <stdlib.h>
#include "weapon.h"

inventory_t *inventory_create(weapon_t *start_weapon)
{
    inventory_t *inventory = NULL;

    inventory = malloc(sizeof(inventory_t));
    if (inventory == NULL)
        return NULL;
    inventory->weapon = start_weapon;
    ASSERT_MALLOC(inventory->weapon, NULL);
    inventory->items = list_init();
    ASSERT_MALLOC(inventory->items, NULL);
    node_append(inventory->items, start_weapon);
    return inventory;
}

void inventory_weapon_destroy(void *weapon)
{
    weapon_t *weapon_cast = (weapon_t *)weapon;

    weapon_destroy(weapon_cast);
}

void inventory_destroy(inventory_t *inventory)
{
    list_destroy(inventory->items, inventory_weapon_destroy);
    free(inventory);
}

void inventory_clear(inventory_t *inv)
{
    while (inv->items->head) {
        node_destroy(inv->items, inventory_weapon_destroy);
    }
}
