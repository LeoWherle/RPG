/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** create a random weapon
*/

#include <stddef.h>
#include <SFML/System.h>
#include <stdlib.h>
#include "entities.h"
#include "text_box.h"
#include "weapon.h"
#include "room.h"

weapon_t *drop_weapon(void)
{
    weapon_t *new = NULL;
    char *file = NULL;
    float cooldown = 0.5;
    int strength = 55;
    int size = 75;

    strength += rand() % 85 - 45;
    if (rand() % 2) {
        size += rand() % 51 - 25;
        cooldown += ((float){rand() % 7 - 3} / 10.);
        file = get_random_file("assets/items/sword");
        new = weapon_create_sword(cooldown, strength,
        (sfVector2f){size, size}, file);
    } else {
        cooldown += (float){rand() % 6} / 10.;
        file = get_random_file("assets/items/bow");
        new = weapon_create_bow(cooldown, strength,
        (sfVector2f){50, 50}, file);
    }
    return new;
}
