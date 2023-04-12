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
