/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** king slime controller
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "entities.h"

void resize_weapon_hitbox(entity_t *slime)
{
    slime->coll.weapon->rect.left += 20;
    slime->coll.weapon->rect.top += 90;
    slime->coll.weapon->rect.width -= 50;
    slime->coll.weapon->rect.height -= 110;
}

int king_slime_camera(entity_t *slime, window_t *window)
{
    if (slime->cam.cam_lock && slime->cam.pass_update && slime->stats.hp > 0) {
        camera_controller(window, slime);
        return 1;
    }
    slime->cam.pass_update = true;
    if (slime->stats.hp <= 0) {
        slime->cam.cam_lock = true;
        slime->coll.weapon->hitbox->activated = false;
        return 1;
    }
    return 0;
}

void king_slime_update(void *slime_void, window_t *window, float delta)
{
    entity_t *slime = (entity_t *)slime_void;
    if (king_slime_camera(slime, window))
        return;
    king_slime_move(slime, window);
    king_slime_jump(slime, window, delta);
    if (slime->state.got_hit)
        enemy_invicibilty(slime, window);
    check_dir(slime, delta);
    if (slime->enemy.king_slime.is_jumping) {
        slime->pos.x += slime->speed_vector.x;
        slime->pos.y += slime->speed_vector.y;
    }
    slime->coll.hitbox = sfSprite_getGlobalBounds(slime->visu.sprite);
    slime->coll.hitbox.top += 20;
    slime->coll.hitbox.width -= 20;
    collision_check(slime->coll.hurt);
    if (slime->coll.weapon->use)
        slime->coll.weapon->use(slime->coll.weapon, window, delta);
    resize_weapon_hitbox(slime);
    enemy_health_bar(slime, 280);
}

void king_slime_print(void *slime_void, window_t *window)
{
    entity_t *slime = (entity_t *)slime_void;

    sfSprite_setPosition(slime->visu.sprite,
    slime->enemy.king_slime.sprite_pos);
    sfCircleShape_setPosition(slime->enemy.king_slime.shadow, slime->pos);
    if (slime->enemy.king_slime.is_jumping)
        sfRenderWindow_drawCircleShape(window->window,
        slime->enemy.king_slime.shadow, NULL);
    sfRenderWindow_drawSprite(window->window, slime->visu.sprite, NULL);
    if (slime->stats.hp < slime->stats.max_hp && slime->stats.hp > 0)
        sfRenderWindow_drawRectangleShape(window->window,
        slime->state.info_bar, NULL);
    if (slime->cam.cam_lock && slime->stats.hp <= 0) {
        sfRenderWindow_drawSprite(window->window,
        slime->visu.death_sprite, NULL);
    }
}

void king_slime_animation(void *slime_void, window_t *window)
{
    entity_t *slime = (entity_t *)slime_void;

    king_slime_anim_controller(slime, window);
}
