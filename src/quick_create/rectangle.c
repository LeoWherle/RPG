/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** make an sfRectangle_shape
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "errorhandling.h"

sfRectangleShape *rectangle_quick_create(sfFloatRect rect,
                        sfTexture *texture, sfColor color)
{
    sfRectangleShape *new = NULL;

    new = sfRectangleShape_create();
    ASSERT_MALLOC(new, NULL);
    sfRectangleShape_setPosition(new, (sfVector2f){rect.left, rect.top});
    sfRectangleShape_setSize(new, (sfVector2f){rect.width, rect.height});
    if (texture) {
        sfRectangleShape_setTexture(new, texture, sfTrue);
    }
    sfRectangleShape_setFillColor(new, color);
    return new;
}
