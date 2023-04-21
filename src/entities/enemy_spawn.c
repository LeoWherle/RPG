/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** enemy_spawn
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"
#include "collision.h"
#include "chained_list.h"
#include "errorhandling.h"
#include "music_player.h"
#include "item.h"
#include "room.h"

void enemy_list_print(void *enemies, window_t *window)
{
    list_t *list = (list_t *)enemies;
    item_t *enemy = NULL;
    node_t *node = list->head;

    while (node) {
        enemy = node->data;
        enemy->print(enemy->item, window);
        node = node->next;
    }
}

void enemy_list_animate(void *enemies, window_t *window)
{
    list_t *list = (list_t *)enemies;
    item_t *enemy = NULL;
    node_t *node = list->head;

    while (node) {
        enemy = node->data;
        enemy->animate(enemy->item, window);
        node = node->next;
    }
}

void remove_enemy_from_list(list_t *list, item_t *enemy, entity_t *enemy_data)
{
    if (enemy_data->enemy.is_dead == 1) {
        if (enemy_data->enemy.is_boss)
            change_music(NULL, VICTORY_M);
        node_delete(list, enemy, destroy_item_enemy);
    }
}

void enemy_list_update(void *enemies, window_t *window, float delta)
{
    list_t *list = (list_t *)enemies;
    item_t *enemy = NULL;
    entity_t *enemy_data = NULL;
    node_t *node = list->head;

    while (node && window->event->type <= 23) {
        enemy = node->data;
        enemy_data = enemy->item;
        enemy->update(enemy_data, window, delta);
        node = node->next;
        if (!enemy_data->enemy.is_boss && enemy_data->stats.hp <= 0) {
            enemy_explosion(enemy_data, window);
            remove_enemy_from_list(list, enemy, enemy_data);
        }
        if (enemy_data->enemy.is_boss && enemy_data->stats.hp <= 0) {
            death_camera_controller(window, enemy_data);
            remove_enemy_from_list(list, enemy, enemy_data);
        }
    }
}
