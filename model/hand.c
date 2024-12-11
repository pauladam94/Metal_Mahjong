#include "../model/align.h"
#include "../utils/better_int.h"
#include "../utils/vec.h"
#include "../view/context.h"
#include "../view/draw.h"
#include "pattern.h"
#include "patterns.h"
#include "player.h"
#include "pos.h"
#include "raylib.h"
#include "tiles.h"
#include <stdlib.h>

typedef struct Hand {
    vec(Tile *) hand;
    vec(Pos *) hand_pos;
    int hand_hover;
    int hand_pressed;

    vec(Tile *) discard;
    vec(Pos *) discard_pos;
    int discard_hover;

    vec(vec(Tile *)) chi;
    vec(vec(Tile *)) pon;
    vec(vec(Tile *)) kan;

    bool opened;
    Align align;
    Vector2 pos;
    Player player;
} Hand;

int hand_get_hand_hover(Hand *hand) { return hand->hand_hover; }
int hand_get_discard_hover(Hand *hand) { return hand->discard_hover; }

void hand_draw(Hand *hand) {
    // hand_update_pos(hand);
    for (u64 i = 0; i < vec_len(hand->hand); i++) {
        tile_draw(hand->hand[i], pos_get(hand->hand_pos[i]), hand->align);
    }
    for (u64 i = 0; i < vec_len(hand->discard); i++) {
        tile_draw(hand->discard[i], pos_get(hand->discard_pos[i]), hand->align);
    }
    if (hand->hand_hover != -1) {
        highlight_tile_draw(pos_get(hand->hand_pos[hand->hand_hover]), ORANGE,
                            hand->align);
    }
    if (hand->discard_hover != -1) {
        highlight_tile_draw(pos_get(hand->discard_pos[hand->discard_hover]),
                            ORANGE, hand->align);
    }
}

Hand *hand_empty(Player player) {
    Hand *hand = calloc(sizeof(*hand), 1);
    hand->hand = NULL;
    hand->discard = NULL;
    hand->align = player_align(player);
    hand->pos = player_pos(player);
    hand->hand_pressed = -1;
    hand->hand_hover = -1;
    hand->discard_hover = -1;
    return hand;
}

void hand_remove_tile(Hand *hand, int pos) {
    vec_remove(hand->hand, pos);
    vec_remove(hand->hand_pos, pos);
}

void hand_add_discard(Hand *hand, Tile *tile) {
    vec_push(hand->discard, tile);
    vec_push(hand->discard_pos, pos_from_vec(align_pos_discard(
                                    hand->align, hand->pos.x, hand->pos.y,
                                    vec_len(hand->discard))));
}

vec(Tile *) hand_discard(Hand *hand) { return hand->discard; }

void hand_discard_tile(Hand *hand, Tile *tile) {
    u64 pos = tiles_remove_equals(hand->hand, tile);
    vec_remove(hand->hand_pos, pos);
    for (u64 i = 0; i < vec_len(hand->hand_pos); i++) {
        hand->hand_pos[i] = pos_from_vec(
            align_pos_hand(hand->align, hand->pos.x, hand->pos.y, i));
    }
    Vector2 prev = pos_get(hand->hand_pos[pos]);
    hand_add_discard(hand, tile);
    // hand_update_pos(hand);
    Vector2 next = pos_get(hand->discard_pos[vec_len(hand->discard_pos) - 1]);
    hand->discard_pos[vec_len(hand->discard) - 1] = pos_transi(prev, next);
}

vec(Tile *) hand_closed_tiles(const Hand *hand) { return hand->hand; }
vec(Tile *) hand_discarded_tiles(const Hand *hand) { return hand->discard; }

void hand_add_tile(Hand *hand, Tile *tile) {
    vec_push(hand->hand, tile);
    vec_push(hand->hand_pos,
             pos_from_vec(align_pos_hand(hand->align, hand->pos.x, hand->pos.y,
                                         vec_len(hand->hand) - 1)));
    // hand_update_pos(hand);
}

bool is_opened(const Hand *hand) { return hand->opened; }
bool is_closed(const Hand *hand) { return !hand->opened; }

void hand_pick_from(Hand *hand, vec(Tile *) from) {
    Tile *t = tiles_pick_from(from);
    hand_add_tile(hand, t);
}

void hand_pp(FILE *file, const Hand *hand) {
    tiles_pp(file, (const vec(Tile *))hand->hand);
}

Patterns *hand_patterns(const Hand *hand) {
    tiles_sort(hand->hand);
    Patterns *res = patterns_empty();
    Patterns *todo = patterns_empty();
    vec(Tile *) tiles = tiles_copy((const vec(Tile *))hand->hand);

    // TODO: Add in the first pattern the different chi and su
    Pattern *pat = pattern_from_tiles(tiles);
    patterns_add_pattern(todo, pat);

    while (patterns_size(todo) != 0) {
        Pattern *pattern = patterns_pop(todo);

        if (pattern_is_complete(pattern)) {
            patterns_add_pattern(res, pattern);
            continue;
        }
        patterns_add_first_group_pattern(todo, pattern);

        // printf("\nRes:\n");
        // patterns_pp(stdout, res);
        // printf("\n");
        // printf("Todo:\n");
        // patterns_pp(stdout, todo);
        // printf("\n");
    }
    patterns_free(todo);
    return res;
}

bool hand_is_complete(const Hand *hand) {
    Patterns *patterns = hand_patterns(hand);

    // printf("Patterns :\n");
    // patterns_pp(stdout, patterns);
    // printf("\n");

    int n_patterns = patterns_size(patterns);
    patterns_free(patterns);
    return n_patterns >= 1;
}

void hand_sort(Hand *hand) { tiles_sort(hand->hand); }

bool hand_is_valid(const Hand *hand) {
    printf("TODO: hand_is_valid\nhand:");
    hand_pp(stdout, hand);
    return true;
}

Hand *hand_from_string(const char *s) {
    Hand *hand = hand_empty(Player0);
    vec_free(hand->hand);
    hand->hand = tiles_from_string(s);
    return hand;
}

void hand_free(Hand *hand) {
    vec_free(hand->hand);
    vec_free(hand->discard);
    for (uint64_t i = 0; i < vec_len(hand->chi); i++)
        vec_free(hand->chi[i]);
    for (uint64_t i = 0; i < vec_len(hand->kan); i++)
        vec_free(hand->kan[i]);
    for (uint64_t i = 0; i < vec_len(hand->pon); i++)
        vec_free(hand->pon[i]);
    vec_free(hand->pon);
    vec_free(hand->chi);
    vec_free(hand->kan);
    free(hand);
}

bool hand_update(Hand *hand, vec(Tile *) tiles, Context ctx) {
    bool next_turn = false;
    // Hand
    hand->hand_pressed = -1;
    hand->hand_hover = -1;
    hand->discard_hover = -1;

    for (uint64_t i = 0; i < vec_len(hand->hand); i++) {
        Rectangle rec = align_rect(hand->align, pos_get(hand->hand_pos[i]));
        if (CheckCollisionPointRec(ctx.mouse, rec)) {
            if (IsMouseButtonDown(0)) {
                hand->hand_pressed = i;
                next_turn = true;
                break;
            } else {
                hand->hand_hover = i;
            }
        }
    }
    // Discard
    for (uint64_t i = 0; i < vec_len(hand->discard); i++) {
        Rectangle rec = align_rect(hand->align, pos_get(hand->discard_pos[i]));
        if (CheckCollisionPointRec(ctx.mouse, rec)) {
            hand->discard_hover = i;
            break;
        }
    }

    if (hand->hand_pressed != -1) {
        Tile *tile_pressed = hand->hand[hand->hand_pressed];

        Tile *random_tile = tiles_random_from((const vec(Tile *))tiles);
        hand_add_tile(hand, random_tile);
        tiles_remove_equals(tiles, random_tile);

        hand_discard_tile(hand, tile_pressed);

        hand_sort(hand);
        hand->hand_pressed = -1; // Back to -1
        hand->hand_hover = -1;   // Back to -1
    }

    return next_turn;
}

void hand_update_pos_transi(Hand *hand) {
    for (u64 i = 0; i < vec_len(hand->hand_pos); i++) {
        pos_update(hand->hand_pos[i]);
    }
    for (u64 i = 0; i < vec_len(hand->discard_pos); i++) {
        pos_update(hand->discard_pos[i]);
    }
}