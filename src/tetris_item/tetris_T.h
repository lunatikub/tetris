#ifndef TETRIS_T_H_
# define TETRIS_T_H_

#define _HT1 (2)
#define _WT1 (3)
/**
 *  X
 * XXX
 */
static inline int tetris_T1_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WT1) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x];
    if (t->h[x + 1] > h) {
        h = t->h[x + 1];
    }
    if (t->h[x + 2] > h) {
        h = t->h[x + 2];
    }

    if (h + _HT1 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HT1;

    /* Update Height */
    t->h[x] = h + 1;
    t->h[x + 1] = h + 2;
    t->h[x + 2] = h + 1;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h, _T);
    _SET(t, x + 1, h, _T);
    _SET(t, x + 2, h, _T);
    _SET(t, x + 1, h - 1, _T);

    return 0;

}

#define _HT2 (3)
#define _WT2 (2)
/**
 * X
 * XX
 * X
 */
static inline int tetris_T2_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WT2) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x];
    if (t->h[x + 1] > 1 && t->h[x + 1] - 1 > h) {
        h = t->h[x + 1]; /* -1 */
    }

    if (h + _HT2 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HT2;

    /* Update Height */
    t->h[x + 1] = h + 2;
    t->h[x] = h + 3;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h, _T);
    _SET(t, x + 1, h - 1, _T);
    _SET(t, x, h - 1, _T);
    _SET(t, x, h - 2, _T);

    return 0;
}

#define _HT3 (2)
#define _WT3 (3)
/**
 * XXX
 *  X
 */
static inline int tetris_T3_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WT3) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x + 1];
    if (t->h[x] > 1 &&
        t->h[x] - 1 > h) {
        h = t->h[x]; /* XXX */
    }
    if (t->h[x + 2] > 1 &&
        t->h[x + 2] - 1 > h) {
        h = t->h[x + 2]; /* XXX */
    }

    if (h + _HT3 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HT3;

    /* Update Height */
    t->h[x + 1] = h + 2;
    t->h[x] = h + 2;
    t->h[x + 2] = h + 2;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h - 1, _T);
    _SET(t, x + 1, h - 1, _T);
    _SET(t, x + 2, h - 1, _T);
    _SET(t, x + 1, h, _T);

    return 0;
}

#define _HT4 (3)
#define _WT4 (2)
/**
 *  X
 * XX
 *  X
 */
static inline int tetris_T4_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WT4) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x + 1];
    if (t->h[x] > 1 &&
        t->h[x] - 1 > h) {
        h = t->h[x] - 1;
    }

    if (h + _HT4 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HT4;

    /* Update Height */
    t->h[x + 1] = h + 3;
    t->h[x] = h + 2;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h - 1, _T);
    _SET(t, x + 1, h - 2, _T);
    _SET(t, x + 1, h - 1, _T);
    _SET(t, x + 1, h, _T);

    return 0;
}

static inline int tetris_T_push(tetris_t *t,
                                T_t       _t,
                                uint8_t   x)
{
    switch (_t) {
        case _T1: return tetris_T1_push(t, x);
        case _T2: return tetris_T2_push(t, x);
        case _T3: return tetris_T3_push(t, x);
        case _T4: return tetris_T4_push(t, x);
        default: return BAD_ITEM;
    }

    return 0;
}

#endif /* !TETRIS_T_H_ */
