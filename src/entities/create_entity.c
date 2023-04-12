/*
** EPITECH PROJECT, 2023
** My_RPG
** File description:
** create_player
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "item.h"
#include "entities.h"
#include "collision.h"
#include "weapon.h"
#include "room.h"

void set_stats(entity_t *entity, stats_t *stats)
{
    entity->stats.hp = stats->hp;
    entity->stats.atk = stats->atk;
    entity->stats.def = stats->def;
    entity->stats.luck = stats->luck;
    entity->stats.speed = stats->speed;
    entity->stats.atk_speed = stats->atk_speed;
}

void set_sprite(entity_t *entity, char *path, sfIntRect anim_rect,
                sfVector2f origin)
{
    entity->texture = sfTexture_createFromFile(path, NULL);
    entity->sprite = sfSprite_create();
    entity->anim_rect = anim_rect;
    sfSprite_setOrigin(entity->sprite, origin);
    sfSprite_setScale(entity->sprite, (sfVector2f){PLAYER_SIZE, PLAYER_SIZE});
    sfSprite_setTexture(entity->sprite, entity->texture, sfTrue);
    sfSprite_setTextureRect(entity->sprite, entity->anim_rect);
    sfSprite_setPosition(entity->sprite, entity->pos);
}

entity_t *create_player(window_t *window, map_t *map)
{
    entity_t *player = malloc(sizeof(entity_t));
    stats_t stats = {PLAYER_HP, PLAYER_ATK, PLAYER_DEF, PLAYER_LUCK,
    PLAYER_SPEED, PLAYER_ATK_SPEED};

    player->dash = malloc(sizeof(player_dash_t));
    player->weapon = weapon_create_sword(0.5, 5, (sfVector2f){50, 50},
    "assets/items/sword.png");
    player->dash->is_dashing = 0;
    player->dash->dash_cooldown = 0;
    player->dash->vector_lock = 0;
    player->got_hit = 0;
    set_sprite(player, "assets/characters/player.png",
    (sfIntRect){0, 0, 48, 48}, (sfVector2f){24, 24});
    set_stats(player, &stats);
    player->hitbox = get_player_bounds(player);
    player->hurt = collider_create(&player->hitbox, HURTBOX, true, player);
    player->hurt->owner = player;
    player->hurt->on_collision_entered = on_hurtbox_enter;
    player->trigger = collider_create(NULL, TRIGGER, false, player);
    player->trigger->on_collision_entered = move_trigger_enter;
    player->depend = malloc(sizeof(dependency_t));
    player->depend->dependency = map;
    player->depend->next = NULL;
    spawn_point(player, '$');
    return player;
}

entity_t *create_slime(window_t *window)
{
    entity_t *slime = malloc(sizeof(entity_t));
    stats_t stats = {100, 10, 0, 0, 2, 0};

    slime->enemy = malloc(sizeof(enemy_t));
    slime->pos = (sfVector2f){window->mode.width / 2 - 500,
    window->mode.height / 2};
    slime->sprite_size = SLIME_SPRITE_SIZE;
    slime->enemy->range = 300;
    slime->enemy->proj_range = CLOSE_RANGE;
    slime->enemy->spoted = 0;
    set_sprite(slime, "assets/characters/Slime.png",
    (sfIntRect){0, 0, SLIME_SPRITE_SIZE, SLIME_SPRITE_SIZE},
    (sfVector2f){10, 0});
    set_stats(slime, &stats);
    slime->hitbox = sfSprite_getGlobalBounds(slime->sprite);
    slime->hurt = collider_create(&slime->hitbox, HURTBOX, true, slime);
    slime->hurt->owner = slime;
    slime->trigger = collider_create(NULL, TRIGGER, false, slime);
    slime->trigger->on_collision_entered = move_trigger_enter;
    return slime;
}
