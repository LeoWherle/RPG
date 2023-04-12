/*
** EPITECH PROJECT, 2023
** Enter hurtbox
** File description:
** RPG
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "item.h"
#include "entities.h"
#include "collision.h"

void on_hurtbox_enter(collider_t *main, collider_t *sub)
{
    entity_t *player = NULL;
    entity_t *enemy = NULL;

    if (sub->type == HURTBOX) {
        player = main->owner;
        enemy = sub->owner;
    }
}