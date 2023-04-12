/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** main
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <unistd.h>
#include <stdlib.h>
#include "entities.h"
#include "errorhandling.h"
#include "gui.h"
#include "menu_values.h"
#include "room.h"

gui_t *create_gui(void)
{
    gui_t *gui = gui_create((sfVector2f){0, -0.48}, "assets/menu/options.png");
    ASSERT_POINTER(gui, NULL);
    gui_t *health_background = gui_sub_create(GUIPOS_HEALTH,
"assets/menu/health_e.png", gui);
    sfRectangleShape_setScale(health_background->shape, (sfVector2f){0.7, 0.7});
    ASSERT_POINTER(health_background, NULL);
    return gui;
}

static item_t *create_entity(item_t *item, window_t *window, gui_t *gui,
map_t *map)
{
    gui_t *hp = NULL;
    entity_t *player = NULL;

    item = item_create(item, create_player(window, map), destroy_player);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, player_update, player_animation, player_print);
    hp = gui_sub_create(GUIPOS_HEALTH, "assets/menu/health_f.png", gui);
    player = (entity_t *)(item->item);
    hp->type = GUI_HEALTH_BAR;
    hp->interactor = &player->stats;
    ASSERT_POINTER(hp, NULL);
    item = item_create(item, create_slime(window), destroy_enemy);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, enemy_update, enemy_animation, enemy_print);
    return (item);
}

item_t *create_item(item_t *item, window_t *window)
{
    map_t *map = NULL;
    gui_t *gui = create_gui();

    item = item_create(item, gui, &gui_destroy);
    ASSERT_POINTER(item, NULL);
    item_set_func(item, NULL, NULL, &gui_draw);
    map = init_map(CAVE_R);
    ASSERT_MALLOC(map, NULL);
    item = item_create(item, map, free_map);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, NULL, NULL, draw_room_second);
    item = create_entity(item, window, gui, map);
    ASSERT_MALLOC(item, NULL);
    item = item_create(item, map, NULL);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, NULL, NULL, draw_room_first);
    return item;
}
