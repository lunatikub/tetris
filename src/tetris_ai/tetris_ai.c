#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "tetris_ai.h"
#include "tetris_map.h"
#include "tetris_x.h"

/**
 * Last item height.
 * ID: l
 * aim: do not increase the map height.
 */
static inline int tetris_eval_l(tetris_t *t)
{
    return t->_e.l; /* set by tetris_XX_push */
}

/**
 * Number of cleared lines with the last item.
 * ID: e
 * aim: encourage to clear lines.
 */
static inline int tetris_eval_e(tetris_t *t)
{
    return t->nr_last_completed;
}

/**
 * Number of transitions between full/empty cell for each lines.
 * ID: dr
 * aim: homogeneous of the map.
 */
static inline int tetris_eval_dr(tetris_t *t)
{
    uint32_t tr = 0;
    uint8_t  y  = 0;
    uint8_t  x  = 0;

    for (y = 0; y < _H; ++y) {
        for (x = 0; x < _W - 1; ++x) {
            if ((_GET(t, x, y) == 0 &&
                 _GET(t, x + 1, y) != 0) ||
                (_GET(t, x, y) &&
                 _GET(t, x + 1, y) == 0)) {
                ++tr;
            }
        }
    }

    return tr;
}

/**
 * Number of transitions between full/empty cell for each cols.
 * ID: dc
 * aim: homogeneous of the map.
 */
static inline int tetris_eval_dc(tetris_t *t)
{
    uint32_t tr = 0;
    uint8_t  y  = 0;
    uint8_t  x  = 0;

    for (x = 0; x < _W; ++x) {
        for (y = 0; y < _H - 1; ++y) {
            if ((_GET(t, x, y) == 0 &&
                 _GET(t, x, y + 1) != 0) ||
                (_GET(t, x, y) &&
                 _GET(t, x, y + 1) == 0)) {
                ++tr;
            }
        }
    }

    return tr;
}

/**
 * Number of holes.
 * ID: L
 * aim: should not have hole.
 */
static inline int tetris_eval_L(tetris_t *t)
{
    uint8_t  x  = 0;
    uint32_t nr = 0;

    for (x = 0; x < _W; ++x) {
        nr += t->hole[x];
    }

    return nr;
}

/**
 * Depth of wells.
 * ID: W
 * aim: should not have well.
 */
static inline int tetris_eval_W(tetris_t *t)
{
    int x = 0;
    int y = 0;

    int seq = 0;
    int well = 0;

    for (x = 0; x < _W; ++x) {
        seq = 0;
        for (y = t->h[x] - 1; y > 0; --y) {
            if (_GET(t, x, _H - y) == 0) {
                ++seq;
                well += seq;
            } else {
                seq = 0;
            }
        }
    }

    return well;
}

static inline int tetris_eval_R(tetris_t *t)
{
    int x = 0;
    int nr = 0;

    for (x = 0; x < _W; ++x) {
        if (t->hole[x] > 0) {
            ++nr;
        }
    }

    return nr;
}

#include "tetris_influence.h"

/**
 * Value / Influence
 */
#define EVAL(v,i) (((double)(v)) * i)

static inline void tetris_eval(tetris_t *t)
{
    t->_e.l  = tetris_eval_l(t);
    t->_e.e  = tetris_eval_e(t);
    t->_e.dr = tetris_eval_dr(t);
    t->_e.dc = tetris_eval_dc(t);
    t->_e.L  = tetris_eval_L(t);
    t->_e.W  = tetris_eval_W(t);
    /* t->_e.R  = tetris_eval_R(t); */
}

/**
 * −l + e − ∆r − ∆c − L − W - D - R
 */
double tetris_score_get(tetris_t *t)
{
    return
        EVAL(t->_e.l,  _Il)  +
        EVAL(t->_e.e,  _Ie)  +
        EVAL(t->_e.dr, _Idr) +
        EVAL(t->_e.dc, _Idc) +
        EVAL(t->_e.L,  _IL)  +
        EVAL(t->_e.W,  _IW);
        /* EVAL(t->_e.R,  _IR); */
}

typedef struct {
    int8_t x;
    int8_t r;
    push_t p;
} ai_move_t;

static inline void tetris_ai_process(tetris_t  *t,
                                     item_t     item,
                                     double    *score,
                                     ai_move_t *mv)
{
    double   tmp_score = 0;
    uint8_t  x = 0;
    uint8_t  r = 0;
    tetris_t t_eval;

    uint32_t _R   = tetris_item_nr_R_get(item);
    push_t   push = tetris_item_push_get(item);

    for (x = 0; x < _W; ++x) {
        for (r = 0; r < _R; ++r) {

            memcpy(&t_eval, t, sizeof(tetris_t));
            if (push(&t_eval, r, x) == OUT_OF_BOUND) {
                continue;
            }

            tetris_map_update(&t_eval);

            tetris_eval(&t_eval);
            tmp_score = tetris_score_get(&t_eval);

            if (_X_) {
                tetris_x_eval_dump(&t_eval, x, r, tmp_score);
            }

            if (tmp_score > *score) {
                *score = tmp_score;
                mv->x = x;
                mv->r = r;
                mv->p = push;
                if (_X_) {
                    tetris_x_score_dump(&t_eval, x, r, *score);
                }
            }
        }
    }
}

int tetris_ai(tetris_t *t,
              item_t    item)
{
    double score = -DBL_MAX;

    ai_move_t mv = {
        .x = -1,
        .r = -1,
        .p = NULL,
    };

    if (_X_) {
        tetris_x_eval_init();
    }

    tetris_ai_process(t, item, &score, &mv);

    /**
     * - Game Over -
     */
    if (mv.x == -1) {
        return -1;
    }

    mv.p(t, mv.r, mv.x);

    return 0;
}
