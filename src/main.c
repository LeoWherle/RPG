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
#include "gui.h"
#include "menu_values.h"
#include "quick_create.h"
#include "errorhandling.h"
#include "my_str.h"
#include "music_player.h"

bool exit_ecs(window_t *window)
{
    if (window->event->type == sfEvtClosed || window->exit) {
        sfRenderWindow_close(window->window);
        window->exit = true;
        return true;
    }
    if (window->state != GAME)
        return true;
    return window->exit;
}

bool exit_menu(window_t *window)
{
    if (window->event->type == sfEvtClosed) {
        window->exit = true;
        return true;
    }
    if (window->state == GAME) {
        return true;
    }
    return window->exit;
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

static int menu_loop(window_t *window)
{
    item_t *item = NULL;
    gui_t *menu = NULL;

    window->state = TITLE_SCREEN;
    menu = gui_create(GUIPOS_BACKGROUND, NULL);
    ASSERT_MALLOC(menu, 1);
    item = item_create(item, menu, gui_destroy);
    ASSERT_MALLOC(item, 1);
    item_set_func(item, &title_screen_update, NULL, &gui_draw);
    menu = menu_create_titlescreen(window, menu);
    ASSERT_MALLOC(menu, 1);
    change_music(NULL, TITLE_SCREEN_M);
    item_loop(item, window, exit_menu);
    item_list_destroy(item);
    return 0;
}

int main(int ac, UNUSED char *av[], char *env[])
{
    window_t *window = NULL;
    item_t *item = NULL;
    int r = 0;
    if (ac != 1 || detect_display(env) == -1) return 84;
    srand(time(NULL));
    window = window_create((sfVideoMode){1920, 1080, 32}, 60,
            "Into the abyss", (sfFloatRect){0, 0, 1920, 1080});
    ASSERT_MALLOC(window, 84);
    item = item_initialization(item, window);
    ASSERT_MALLOC(item, 84);
    while (!window->exit && window->state != EXIT_ERROR) {
        if (menu_loop(window) != 1) {
            item_loop(item, window, exit_ecs);
        } else
            window->state = EXIT_ERROR;
    }
    r = (window->state == EXIT_ERROR) ? 84 : 0;
    item_list_destroy(item);
    window_destroy(window);
    return r;
}
