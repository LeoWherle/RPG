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
#include "projectile.h"
#include "text_box.h"
#include "music_player.h"

static item_t *create_weapons(item_t *item)
{
    projectile_t *proj = NULL;

    proj = projectile_create((sfFloatRect){0}, (sfVector2f){0}, NULL, NULL);
    ASSERT_MALLOC(proj, NULL);
    item = item_create(item, proj->projectile_list, projectile_list_destroy);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, projectile_update, NULL, projectile_print);
    node_delete(proj->projectile_list, proj, projectile_delete);
    return (item);
}

static item_t *create_entity(item_t *item, gui_t *gui, map_t *map,
window_t *window)
{
    gui_t *bar = NULL;

    item = item_create(item, spawn_enemies(map), clear_list);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, enemy_list_update, enemy_list_animate,
    enemy_list_print);
    item = item_create(item, create_player(map, window), destroy_player);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, player_update, player_animation, player_print);
    window->player = item->item;
    bar = bars_init(gui->sub_gui_list->head->data, item);
    ASSERT_POINTER(bar, NULL);
    bar = menu_create_inventory(gui, window, item);
    item = create_weapons(item);
    ASSERT_MALLOC(item, NULL);
    return (item);
}

static item_t *create_text(item_t *item)
{
    sfFont *font = sfFont_createFromFile("assets/font/Monocraft.otf");

    ASSERT_MALLOC(font, NULL);
    item = item_create(item, text_box_create(font, NULL), text_box_destroy);
    ASSERT_POINTER(item, NULL);
    item_set_func(item, text_box_update, NULL, text_box_print);
    item = item_create(item, music_player_create(font), music_player_destroy);
    ASSERT_POINTER(item, NULL);
    item_set_func(item, music_update, NULL, music_print);
    return item;
}

item_t *item_initialization(item_t *item, window_t *window)
{
    map_t *map = NULL;
    gui_t *gui = create_gui(window);

    item = item_create(item, gui, &gui_destroy);
    ASSERT_POINTER(item, NULL);
    item_set_func(item, &gui_update, NULL, &gui_draw);
    item = create_text(item);
    ASSERT_MALLOC(item, NULL);
    map = init_map(HOUSE_R, map);
    ASSERT_MALLOC(map, NULL);
    item = item_create(item, map, free_map);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, NULL, NULL, draw_room_second);
    item = create_entity(item, gui, map, window);
    ASSERT_MALLOC(item, NULL);
    item = item_create(item, map, NULL);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, NULL, NULL, draw_room_first);
    return item;
}
