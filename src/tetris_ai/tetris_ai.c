#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "tetris_ai.h"
#include "tetris_wall.h"
#include "tetris_x.h"
#include "tetris_hold.h"

/**
 * Last item height.
 * ID: l
 * aim: do not increase the wall height.
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
 * aim: homogeneous of the wall.
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
 * aim: homogeneous of the wall.
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

static inline int tetris_well_sum(int h_well)
{
    int seq = 0;
    int well = 0;

    for (seq = 0; seq < h_well; ++seq) {
        well += (seq + 1);
    }

    return well;
}

/**
 * Depth of wells.
 * ID: W
 * aim: should not have well.
 */
static inline int tetris_eval_W(tetris_t *t)
{
    int x = 0;

    int well = 0;
    int h_last = 0;
    int h_warn = 0;

    if (t->h[0] < t->h[1]) {
        well += tetris_well_sum(t->h[1] - t->h[0]);
    }

    for (x = 0; x < _W; ++x) {
        if (x != 0) {
            if (h_warn) {
                if (t->h[x] > h_last) {
                    int min = t->h[x] > h_warn ? h_warn : t->h[x];
                    well += tetris_well_sum(min - h_last);
                }
                h_warn = 0;
            }

            if (t->h[x] < h_last) {
                h_warn = h_last;
            }
        }
        h_last = t->h[x];
    }

    if (t->h[_W - 2] > t->h[_W - 1]) {
        well += tetris_well_sum(t->h[_W - 2] - t->h[_W - 1]);
    }

    return well;
}

#include "tetris_influence.h"

/**
 * Value / Influence
 */
#define EVAL(v,i) (((int)(v)) * i)

void tetris_eval(tetris_t *t)
{
    t->_e.l  = tetris_eval_l(t);
    t->_e.e  = tetris_eval_e(t);
    t->_e.dr = tetris_eval_dr(t);
    t->_e.dc = tetris_eval_dc(t);
    t->_e.L  = tetris_eval_L(t);
    t->_e.W  = tetris_eval_W(t);
}

/**
 * −l + e − ∆r − ∆c − 4L − W - D - R
 */
static inline int tetris_score_get(tetris_t *t)
{
    return
        EVAL(t->_e.l,  _Il)  +
        EVAL(t->_e.e,  _Ie)  +
        EVAL(t->_e.dr, _Idr) +
        EVAL(t->_e.dc, _Idc) +
        EVAL(t->_e.L,  _IL)  * 4 +
        EVAL(t->_e.W,  _IW);
}

static inline push_t tetris_ai_process(tetris_t *t,
                                       item_t    item,
                                       int      *score,
                                       move_t   *mv)
{
    int      tmp_score = 0;
    uint8_t  x         = 0;
    uint8_t  r         = 0;
    tetris_t t_eval;
    push_t   _push     = NULL;

    uint32_t _R   = tetris_item_nr_R_get(item);
    push_t   push = tetris_item_push_get(item);

    for (x = 0; x < _W; ++x) {
        for (r = 0; r < _R; ++r) {

            memcpy(&t_eval, t, sizeof(tetris_t));
            if (push(&t_eval, r, x) == OUT_OF_BOUND) {
                continue;
            }

            tetris_wall_update(&t_eval);

            tetris_eval(&t_eval);
            tmp_score = tetris_score_get(&t_eval);

            if (_X_) {
                tetris_x_eval_dump(&t_eval, x, r, tmp_score);
            }

            if (tmp_score > *score) {
                *score = tmp_score;
                mv->x = x;
                mv->r = r;
                _push = push;
                if (_X_) {
                    tetris_x_score_dump(&t_eval, x, r, *score);
                }
            }
        }
    }

    return _push;
}

int tetris_ai(tetris_t *t,
              item_t    curr_item,
              item_t   *items,
              move_t   *mv)
{
    int    score     = -INT_MAX;
    push_t push      = NULL;
    push_t hold_push = NULL;

    (void)items;

    mv->x = -1;
    mv->r = -1;
    mv->hold = 0;

    if (_X_) {
        tetris_x_eval_init();
    }

    if (t->nr_items == 0 &&
        (curr_item == _S || curr_item == _Z)) {
        tetris_hold_set(t, curr_item);
        ++t->nr_items;
        return 0;
    }

    push = tetris_ai_process(t, curr_item, &score, mv);

    if (tetris_hold_is_empty(t) == 0 && t->nr_items != 1 && t->hold != curr_item) {
        hold_push = tetris_ai_process(t, t->hold, &score, mv);
    }

    if (tetris_hold_is_empty(t) && t->nr_items != 0 && (t->score - score > GAP_SCORE_HOLD)) {
        tetris_hold_set(t, curr_item);
        return 0;
    }

    if (hold_push != NULL) {
        tetris_hold_set(t, curr_item);
        push = hold_push;
        mv->hold = 1;
    }

    /**
     * --- Game Over ---
     */
    if (mv->x == -1) {
        return -1;
    }

    push(t, mv->r, mv->x);
    ++t->nr_items;
    t->score = score;

    return 0;
}
