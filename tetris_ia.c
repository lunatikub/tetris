#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tetris_ia.h"
#include "tetris_map.h"

#define PENALITY_LEVEL_INFLUENCE  (100)
#define PENALITY_HOLE_INFLUENCE   (100000)
#define PENALITY_HEIGHT_INFLUENCE (500)

static inline uint32_t tetris_map_eval(tetris_t *t)
{
    uint32_t x = 0;
    uint32_t score = 0;
    uint32_t penality = 0;

    int8_t max_h = _H - 1;

    while (max_h > 0 && t->h[max_h] != 0) {
        --max_h;
    }

    /* HEIGHT INFLUENCE */
    score += max_h * PENALITY_HEIGHT_INFLUENCE;

    score += t->hole[0] * PENALITY_HOLE_INFLUENCE;

    for (x = 1; x < _W; ++x) {
        /* LEVEL INFLUENCE */
        penality = abs(t->h[x - 1] - t->h[x]);
        penality *= penality;
        penality *= PENALITY_LEVEL_INFLUENCE;
        score += penality;
        /* HOLE INFLUENCE */
        score += t->hole[x] * PENALITY_HOLE_INFLUENCE;
    }

    return score;
}

void tetris_next_move_get(tetris_t *t,
                          item_t    item,
                          move_t   *move)
{
    uint32_t score     = UINT32_MAX;
    uint32_t tmp_score = 0;
    uint32_t _R        = 0;
    uint8_t  x         = 0;
    uint8_t  r         = 0;
    push_t   push      = NULL;

    switch (item) {
        case _I: _R = _INR; push = tetris_I_push; break;
        case _J: _R = _JNR; push = tetris_J_push; break;
        case _L: _R = _LNR; push = tetris_L_push; break;
        case _O: _R = _ONR; push = tetris_O_push; break;
        case _S: _R = _SNR; push = tetris_S_push; break;
        case _T: _R = _TNR; push = tetris_T_push; break;
        case _Z: _R = _ZNR; push = tetris_Z_push; break;
        default: ;
    }

    tetris_t t_eval;

    for (x = 0; x < _W; ++x) {
        for (r = 0; r < _R; ++r) {
            memcpy(&t_eval, t, sizeof(tetris_t));
            if (push(&t_eval, r, x) == OUT_OF_BOUND) {
                continue;
            }
            tetris_hole_update(&t_eval);
            tetris_map_update(&t_eval);
            tmp_score = tetris_map_eval(&t_eval);
            if (tmp_score < score) {
                score = tmp_score;
                move->r = r;
                move->x = x;
                move->p = push;
            }
        }
    }
}
