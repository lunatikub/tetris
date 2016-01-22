#ifndef TETRIS_S_H_
# define TETRIS_S_H_

#define _HS1 (2)
#define _WS1 (3)
/**
 *  XX
 * XX
 */
static inline int tetris_S1_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WS1) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x] + 1;
    if (t->h[x + 1] + 1 > h) {
        h = t->h[x + 1] + 1;
    }
    if (t->h[x + 2] > h) {
        h = t->h[x + 2];
    }

    if (h + _HS1 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h - 1 + _HS1;

    /* Update Height */
    t->h[x] = h;
    t->h[x + 1] = h + 1;
    t->h[x + 2] = h + 1;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h + 1, _S);
    _SET(t, x + 1, h, _S);
    _SET(t, x + 1, h + 1, _S);
    _SET(t, x + 2, h, _S);

    return 0;
}

#define _HS2 (3)
#define _WS2 (2)
/**
 * X
 * XX
 *  X
 */
static inline int tetris_S2_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WS2) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x + 1];
    if (t->h[x] > 1 &&
        t->h[x] - 1 > h) {
        h = t->h[x] - 1;
    }

    if (h + _HS2 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HS2;

    /* Update Height and Hole */
    t->h[x + 1] = h + 2;
    t->h[x] = t->h[x + 1] + 1;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h - 1, _S);
    _SET(t, x, h - 2, _S);
    _SET(t, x + 1, h - 1, _S);
    _SET(t, x + 1, h, _S);

    return 0;
}

static inline int tetris_S_push(tetris_t *t,
                                S_t       _s,
                                uint8_t   x)
{
    switch (_s) {
        case _S1: return tetris_S1_push(t, x);
        case _S2: return tetris_S2_push(t, x);
        default: return BAD_ITEM;
    }

    return 0;
}

#endif /* !TETRIS_S_H_ */
