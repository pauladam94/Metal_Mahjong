#include "pattern.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Patterns {
    int cap;
    int len;
    Pattern **arr;
} Patterns;

void patterns_pp(FILE *file, const Patterns *patterns) {
    for (int i = 0; i < patterns->len; i++) {
        fprintf(file, "Pat %d :", i);
        pattern_pp(file, patterns->arr[i]);
        if (i != patterns->len - 1) {
            fprintf(file, "\n");
        }
    }
}

Patterns *patterns_empty(void) {
    Patterns *patterns = calloc(sizeof(*patterns), 1);
    return patterns;
}

void patterns_add_pattern(Patterns *patterns, Pattern *pat) {
    patterns->len++;
    if (patterns->len > patterns->cap) {
        patterns->cap = patterns->cap == 0 ? 1 : patterns->cap * 2;
        patterns->arr =
            realloc(patterns->arr, sizeof(patterns->arr) * patterns->cap);
    }
    patterns->arr[patterns->len - 1] = pat;
}

Pattern *patterns_pop(Patterns *patterns) {
    if (patterns->len == 0) {
        fprintf(stderr, "Pop on an Empty Pattern");
        exit(1);
    }
    patterns->len--;
    return patterns->arr[patterns->len];
}

int patterns_size(const Patterns *patterns) { return patterns->len; }

void patterns_add_first_group_pattern(Patterns *patterns, Pattern *pat) {
    // FIRST SEQUENCE
    Tile *fst = NULL;
    Tile *snd = NULL;
    Tile *thrd = NULL;
    pattern_next_sequence(pat, &fst, &snd, &thrd);
    if (fst != NULL && snd != NULL && thrd != NULL &&
        !pattern_has_four_group(pat)) {
        Pattern *new_pattern = pattern_copy(pat);
        pattern_add_group(new_pattern, fst, snd, thrd);
        pattern_remove_tile(new_pattern, fst);
        pattern_remove_tile(new_pattern, snd);
        pattern_remove_tile(new_pattern, thrd);
        patterns_add_pattern(patterns, new_pattern);
    }
    // FIRST THREE OF A KIND
    fst = NULL;
    snd = NULL;
    thrd = NULL;
    pattern_next_three_same(pat, &fst, &snd, &thrd);
    if (fst != NULL && snd != NULL && thrd != NULL &&
        !pattern_has_four_group(pat)) {
        Pattern *new_pattern = pattern_copy(pat);
        pattern_add_group(new_pattern, fst, snd, thrd);
        pattern_remove_tile(new_pattern, fst);
        pattern_remove_tile(new_pattern, snd);
        pattern_remove_tile(new_pattern, thrd);
        patterns_add_pattern(patterns, new_pattern);
    }
    // FIRST PAIR
    fst = NULL;
    snd = NULL;
    pattern_next_pair(pat, &fst, &snd);
    if (fst != NULL && snd != NULL && !pattern_has_pair(pat)) {
        Pattern *new_pattern = pattern_copy(pat);
        pattern_add_pair(new_pattern, fst, snd);
        pattern_remove_tile(new_pattern, fst);
        pattern_remove_tile(new_pattern, snd);
        patterns_add_pattern(patterns, new_pattern);
    }
    pattern_free(pat);
    /*
    Tile *t = pattern_get_tile(pat, 0);
    if (t != NULL) {
        pattern_remove_tile(pat, t);
        patterns_add_pattern(patterns, pat);
    } else {
        pattern_free(pat);
    }
    */
}

void patterns_free(Patterns *patterns) {
    for (int i = 0; i < patterns->len; i++) {
        pattern_free(patterns->arr[i]);
        patterns->arr[i] = NULL;
    }
    free(patterns->arr);
    free(patterns);
}
