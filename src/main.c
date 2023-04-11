/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** main
*/

#include <SFML/System.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "item.h"
#include "room.h"
#include "entities.h"
#include "errorhandling.h"
#include "my_str.h"
#include "gui.h"
#include "menu_values.h"

bool exit_ecs(window_t *window)
{
    if (window->event->type == sfEvtClosed) {
        sfRenderWindow_close(window->window);
        return true;
    }
    return false;
}

static int detect_display(char *env[])
{
    int i = 0;

    if (env[0] == NULL)
        return (-1);
    while (env[i]) {
        if (my_env_strcmp(env[i], "DISPLAY") == 0) {
            return (0);
        }
        i++;
    }
    write(2, "No display detected :(\n", 23);
    return (-1);
}

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

static item_t *create_entity(item_t *item, window_t *window, gui_t *gui)
{
    gui_t *hp = NULL;
    entity_t *player = NULL;

    item = item_create(item, create_player(window), destroy_player);
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
    item = create_entity(item, window, gui);
    ASSERT_MALLOC(item, NULL);
    item = item_create(item, map, NULL);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, NULL, NULL, draw_room_first);
    return item;
}

int main(int ac, UNUSED char *av[], char *env[])
{
    window_t *window = NULL;
    item_t *item = NULL;

    if (ac != 1 || detect_display(env) == -1)
        return 84;
    srand(time(NULL));
    window = window_create((sfVideoMode){1920, 1080, 32}, 60,
            "Into the abyss", (sfFloatRect){0, 0, 1920, 1080});
    ASSERT_MALLOC(window, 84);
    item = create_item(item, window);
    ASSERT_MALLOC(item, 84);
    item_loop(item, window, exit_ecs);
    item_list_destroy(item);
    window_destroy(window);
    return 0;
}
