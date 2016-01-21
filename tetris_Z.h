#ifndef TETRIS_Z_H_
# define TETRIS_Z_H_

#define _HZ1 (2)
#define _WZ1 (3)
/**
 * XX
 *  XX
 */
static inline int tetris_Z1_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WZ1) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x];
    if (t->h[x + 1] + 1 > h) {
        h = t->h[x + 1] + 1;
    }
    if (t->h[x + 2] + 1 > h) {
        h = t->h[x + 2] + 1;
    }

    if (h + _HZ1 > _H) {
        return OUT_OF_BOUND;
    }

    /* Update Height */
    t->h[x] = h + 1;
    t->h[x + 1] = h + 1;
    t->h[x + 2] = h;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h, _Z);
    _SET(t, x + 1, h + 1, _Z);
    _SET(t, x + 1, h, _Z);
    _SET(t, x + 2, h + 1, _Z);

    return 0;
}

#define _HZ2 (3)
#define _WZ2 (2)
/**
 *  X
 * XX
 * X
 */
static inline int tetris_Z2_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WI1) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x];
    if (t->h[x + 1] > 1 &&
        t->h[x + 1] - 1 > h) {
        h = t->h[x + 1]; /* XXX */
    }

    if (h + _HZ2 > _H) {
        return OUT_OF_BOUND;
    }

    /* Update Height */
    t->h[x + 1] = h + 3;
    t->h[x] = h + 2;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h, _Z);
    _SET(t, x, h - 1, _Z);
    _SET(t, x + 1, h - 1, _Z);
    _SET(t, x + 1, h - 2, _Z);

    return 0;
}

static inline int tetris_Z_push(tetris_t *t,
                                Z_t       _z,
                                uint8_t   x)
{
    switch (_z) {
        case _Z1: return tetris_Z1_push(t, x);
        case _Z2: return tetris_Z2_push(t, x);
        default: return BAD_ITEM;
    }

    return 0;
}

#endif /* !TETRIS_Z_H_ */
