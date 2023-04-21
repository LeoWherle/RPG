/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** chest drop
*/

#include <stdlib.h>
#include "entities.h"
#include "text_box.h"
#include "weapon.h"
#include "room.h"

void interact_empty_chest(UNUSED entity_t *player, UNUSED collider_t *chest)
{
    text_box_modify(NULL, " Narrator\0", "\tSadly this chest is empty...\0", 1);
}

void interact_chest(entity_t *player, collider_t *chest)
{
    window_t *window = player->depend->next->dependency;
    weapon_t *new = NULL;
    int error = 0;

    if (player->inventory->items->size >= INV_SLOT_MAX) {
        return (text_box_modify(NULL, " Narrator\0", "\tYour inventory is \
full, you can't take anything else. :(\0", 1));
    }
    new = drop_weapon();
    error = node_append(player->inventory->items, new);
    if (!new || error == 1) {
        window->state = EXIT_ERROR;
        return;
    }
    new->hitbox->owner = player;
    chest->owner = interact_empty_chest;
    text_box_modify(NULL, " Narrator\0", "\tYou opened the chest, \
what could be in it ?\n\tCheck your inventory to see it\0", 1);
}
