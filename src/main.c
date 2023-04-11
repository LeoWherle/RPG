/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** main
*/

#include <SFML/System.h>
#include <stdbool.h>
#include <unistd.h>
#include "item.h"
#include "room.h"
#include "entities.h"
#include "errorhandling.h"
#include "my_str.h"

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

item_t *item_creator(item_t *item, window_t *window)
{
    map_t *map = NULL;

    map = init_map(VILLAGE_R);
    ASSERT_MALLOC(map, NULL);
    item = item_create(item, map, free_map);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, NULL, NULL, draw_room_second);
    item = item_create(item, create_player(window), destroy_player);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, player_update, player_animation, player_print);
    item = item_create(item, create_slime(window), destroy_enemy);
    ASSERT_MALLOC(item, NULL);
    item_set_func(item, enemy_update, NULL, enemy_print);
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
    window = window_create((sfVideoMode){1920, 1080, 32}, 60,
            "Into the abyss", (sfFloatRect){0, 0, 1920, 1080});
    ASSERT_MALLOC(window, 84);
    item = item_creator(item, window);
    ASSERT_MALLOC(item, 84);
    item_loop(item, window, exit_ecs);
    item_list_destroy(item);
    window_destroy(window);
    return 0;
}
