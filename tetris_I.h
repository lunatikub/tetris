#ifndef TETRIS_I_H_
# define TETRIS_I_H_

#define _WI1 (4)
#define _HI1 (1)
/**
 * XXXX
 */
static inline int tetris_I1_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WI1) {
        return OUT_OF_BOUND;
    }

    /* Max height */
    h = t->h[x];
    if (t->h[x + 1] > h) {
        h = t->h[x + 1];
    }
    if (t->h[x + 2] > h) {
        h = t->h[x + 2];
    }
    if (t->h[x + 3] > h) {
        h = t->h[x + 3];
    }

    if (h + _HI1 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HI1;

    /* Update Height and Hole */
    t->h[x] = h + 1;
    t->h[x + 1] = h + 1;
    t->h[x + 2] = h + 1;
    t->h[x + 3] = h + 1;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h, _I);
    _SET(t, x + 1, h, _I);
    _SET(t, x + 2, h, _I);
    _SET(t, x + 3, h, _I);

    return 0;
}

#define _HI2 (4)
#define _WI2 (1)
/**
 * X
 * X
 * X
 * X
 */
static inline int tetris_I2_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WI2) {
        return OUT_OF_BOUND;
    }

    h = t->h[x];
    t->h[x] = h + 4;

    if (h + _HI2 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HI2;

    h = _H - h - 1;

    _SET(t, x, h, _I);
    _SET(t, x, h - 1, _I);
    _SET(t, x, h - 2, _I);
    _SET(t, x, h - 3, _I);

    return 0;
}

static inline int tetris_I_push(tetris_t *t,
                                 I_t       _i,
                                 uint8_t   x)
{
    switch (_i) {
        case _I1: return tetris_I1_push(t, x);
        case _I2: return tetris_I2_push(t, x);
        default: return BAD_ITEM;
    }

    return 0;
}

#endif /* !TETRIS_I_H_ */
