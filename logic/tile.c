#include "tile.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    None = 0, // is O
    M1, // Man 1
    M2, // ...
    M3,
    M4,
    M5,
    M6,
    M7,
    M8,
    M9,
    P1, // Pin 1
    P2, // ...
    P3,
    P4,
    P5,
    P6,
    P7,
    P8,
    P9,
    S1, // Su 1
    S2, // ...
    S3,
    S4,
    S5,
    S6,
    S7,
    S8,
    S9,
    Z1, // East Wind
    Z2, // South Wind
    Z3, // West Wind
    Z4, // North Wind
    Z5, // White Dragon
    Z6, // Green Dragon
    Z7  // Red Dragon
} _Tile;

typedef struct Tile {
} Tile;

int tile_comp(const Tile *t0, const Tile *t1) {
    _Tile _t0 = (uint64_t)t0;
    _Tile _t1 = (uint64_t)t1;
    if (_t0 > _t1) {
        return 1;
    } else if (_t0 < _t1) {
        return -1;
    } else {
        return 0;
    }
}

int tile_number(const Tile *t) {
    switch ((_Tile)(uint64_t)t) {
    case M1:
    case P1:
    case S1:
        return 1;
    case M2:
    case P2:
    case S2:
        return 2;
    case M3:
    case P3:
    case S3:
        return 3;
    case M4:
    case P4:
    case S4:
        return 4;
    case M5:
    case P5:
    case S5:
        return 5;
    case M6:
    case P6:
    case S6:
        return 6;
    case M7:
    case P7:
    case S7:
        return 7;
    case M8:
    case P8:
    case S8:
        return 8;
    case M9:
    case P9:
    case S9:
        return 9;
    case Z1:
    case Z2:
    case Z3:
    case Z4:
    case Z5:
    case Z6:
    case Z7:
    case None:
        return -1;
    }
}

bool tile_is_honor(const Tile *t) {
    return (Z1 <= (uint64_t)t && (uint64_t)t <= Z7);
}
bool tile_is_dragon(const Tile *t) {
    return (Z5 <= (uint64_t)t && (uint64_t)t <= Z7);
}
bool tile_is_wind(const Tile *t) {
    return (Z1 <= (uint64_t)t && (uint64_t)t <= Z4);
}
bool tile_is_family(const Tile *t) { return !tile_is_honor(t); }
bool tile_is_man(const Tile *t) {
    return (M1 <= (uint64_t)t && (uint64_t)t <= M9);
}
bool tile_is_pin(const Tile *t) {
    return (P1 <= (uint64_t)t && (uint64_t)t <= P9);
}
bool tile_is_su(const Tile *t) {
    return (S1 <= (uint64_t)t && (uint64_t)t <= S9);
}
bool tile_same_family(const Tile *t0, const Tile *t1) {
    return ((tile_is_man(t0) && tile_is_man(t1)) ||
            (tile_is_pin(t0) && tile_is_pin(t1)) ||
            (tile_is_su(t0) && tile_is_su(t1)));
}
bool tile_adjacent(const Tile *t0, const Tile *t1) {
    return (tile_is_family(t0) && tile_is_family(t1) &&
            (tile_same_family(t0, t1)) &&
            ((tile_number(t0) == tile_number(t1) + 1) ||
             tile_number(t0) + 1 == tile_number(t1)));
};

// 1m for Man number 1
// 1s for Su, 1p for Pin
// then 1z to 7z for winds and dragons
Tile *tile_from_string(const char *name) {
    if (strlen(name) != 2) {
        fprintf(stderr,
                "Error : %s not describe a tile. Do 1m or 4s or 2z instead.\n",
                name);
        exit(1);
    }
    _Tile res;
    switch (name[1]) {
    case 'm':
        res = M1 + ((int)name[0] - '0') - 1;
        break;
    case 'p':
        res = P1 + ((int)name[0] - '0') - 1;
        break;
    case 's':
        res = S1 + ((int)name[0] - '0') - 1;
        break;
    case 'z':
        res = Z1 + ((int)name[0] - '0') - 1;
        break;
    }
    return (Tile *)res;
}

static Texture2D *tiles_textures = NULL;
static bool loaded_has_been_done = false;

void load_all_tiles() {
    loaded_has_been_done = true;
    tiles_textures = calloc(sizeof(*tiles_textures), Z7 + 1);
    tiles_textures[M1] = LoadTexture("data/C1.png");
    tiles_textures[M2] = LoadTexture("data/C2.png");
    tiles_textures[M3] = LoadTexture("data/C3.png");
    tiles_textures[M4] = LoadTexture("data/C4.png");
    tiles_textures[M5] = LoadTexture("data/C5.png");
    tiles_textures[M6] = LoadTexture("data/C6.png");
    tiles_textures[M7] = LoadTexture("data/C7.png");
    tiles_textures[M8] = LoadTexture("data/C8.png");
    tiles_textures[M9] = LoadTexture("data/C9.png");
    tiles_textures[P1] = LoadTexture("data/R1.png");
    tiles_textures[P2] = LoadTexture("data/R2.png");
    tiles_textures[P3] = LoadTexture("data/R3.png");
    tiles_textures[P4] = LoadTexture("data/R4.png");
    tiles_textures[P5] = LoadTexture("data/R5.png");
    tiles_textures[P6] = LoadTexture("data/R6.png");
    tiles_textures[P7] = LoadTexture("data/R7.png");
    tiles_textures[P8] = LoadTexture("data/R8.png");
    tiles_textures[P9] = LoadTexture("data/R9.png");
    tiles_textures[S1] = LoadTexture("data/B1.png");
    tiles_textures[S2] = LoadTexture("data/B2.png");
    tiles_textures[S3] = LoadTexture("data/B3.png");
    tiles_textures[S4] = LoadTexture("data/B4.png");
    tiles_textures[S5] = LoadTexture("data/B5.png");
    tiles_textures[S6] = LoadTexture("data/B6.png");
    tiles_textures[S7] = LoadTexture("data/B7.png");
    tiles_textures[S8] = LoadTexture("data/B8.png");
    tiles_textures[S9] = LoadTexture("data/B9.png");
    tiles_textures[Z1] = LoadTexture("data/VE.png");
    tiles_textures[Z2] = LoadTexture("data/VS.png");
    tiles_textures[Z3] = LoadTexture("data/VO.png");
    tiles_textures[Z4] = LoadTexture("data/VN.png");
    tiles_textures[Z5] = LoadTexture("data/DB.png");
    tiles_textures[Z6] = LoadTexture("data/DV.png");
    tiles_textures[Z7] = LoadTexture("data/DR.png");

    for (int i = M1; i <= Z7; i++) {
        SetTextureFilter(tiles_textures[i], TEXTURE_FILTER_TRILINEAR);
    }
}

Tile *tile_random(void) { return (Tile *)(uint64_t)(rand() % (Z7 + 1)); }
Texture2D tile_texture(const Tile *t) {
    if (!loaded_has_been_done) {
        load_all_tiles();
    }
    return tiles_textures[(uint64_t)t];
}

void tiles_free_textures() {
    for (size_t i = M1; i <= Z7; i++) {
        UnloadTexture(tiles_textures[i]);
    }
    loaded_has_been_done = false;
    free(tiles_textures);
    tiles_textures = NULL;
}

void tile_pp(FILE *file, const Tile *t) {
    switch ((_Tile)(uint64_t)t) {
    case None:
        fprintf(file, "None");
    case M1:
        fprintf(file, "1m");
        break;
    case P1:
        fprintf(file, "1p");
        break;
    case S1:
        fprintf(file, "1s");
        break;
    case M2:
        fprintf(file, "2m");
        break;
    case P2:
        fprintf(file, "2p");
        break;
    case S2:
        fprintf(file, "2s");
        break;
    case M3:
        fprintf(file, "3m");
        break;
    case P3:
        fprintf(file, "3p");
        break;
    case S3:
        fprintf(file, "3s");
        break;
    case M4:
        fprintf(file, "4m");
        break;
    case P4:
        fprintf(file, "4p");
        break;
    case S4:
        fprintf(file, "4s");
        break;
    case M5:
        fprintf(file, "5m");
        break;
    case P5:
        fprintf(file, "5p");
        break;
    case S5:
        fprintf(file, "5s");
        break;
    case M6:
        fprintf(file, "6m");
        break;
    case P6:
        fprintf(file, "6p");
        break;
    case S6:
        fprintf(file, "6s");
        break;
    case M7:
        fprintf(file, "7m");
        break;
    case P7:
        fprintf(file, "7p");
        break;
    case S7:
        fprintf(file, "7s");
        break;
    case M8:
        fprintf(file, "8m");
        break;
    case P8:
        fprintf(file, "8p");
        break;
    case S8:
        fprintf(file, "8s");
        break;
    case M9:
        fprintf(file, "9m");
        break;
    case P9:
        fprintf(file, "9p");
        break;
    case S9:
        fprintf(file, "9s");
        break;
    case Z1:
        fprintf(file, "1z");
        break;
    case Z2:
        fprintf(file, "2z");
        break;
    case Z3:
        fprintf(file, "3z");
        break;
    case Z4:
        fprintf(file, "4z");
        break;
    case Z5:
        fprintf(file, "5z");
        break;
    case Z6:
        fprintf(file, "6z");
        break;
    case Z7:
        fprintf(file, "7z");
        break;
    }
}

void tile_free(Tile *tile) {}
bool tile_equals(const Tile *t1, const Tile *t2) { return t1 == t2; }

Tile *next_dora(const Tile *tile) {
    _Tile res;
    switch ((_Tile)(uint64_t)tile) {
    case M1:
    case P1:
    case S1:
    case M2:
    case P2:
    case S2:
    case M3:
    case P3:
    case S3:
    case M4:
    case P4:
    case S4:
    case M5:
    case P5:
    case S5:
    case M6:
    case P6:
    case S6:
    case M7:
    case P7:
    case S7:
    case M8:
    case P8:
    case S8:
    case Z1:
    case Z2:
    case Z3:
    case Z5:
    case Z6:
        res = (_Tile)(uint64_t)tile + 1;
        break;
    case M9:
    case P9:
    case S9:
        res = (_Tile)(uint64_t)tile - 8;
        break;
    case Z4:
        res = (_Tile)(uint64_t)tile - 3;
        break;
    case Z7:
        res = (_Tile)(uint64_t)tile - 2;
        break;
    }
    return (Tile *)res;
}
