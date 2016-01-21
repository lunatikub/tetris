#ifndef TETRIS_J_H_
# define TETRIS_J_H_

#define _HJ1 (2)
#define _WJ1 (3)
/**
 * X
 * XXX
 */
static inline int tetris_J1_push(tetris_t *t,
                                  uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WJ1) {
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

    if (h + _HJ1 > _H) {
        return OUT_OF_BOUND;
    }

    /* Update Height and Hole */
    t->h[x] = h + 2;
    t->h[x + 1] = h + 1;
    t->h[x + 2] = h + 1;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h, _J);
    _SET(t, x, h - 1, _J);
    _SET(t, x + 1, h, _J);
    _SET(t, x + 2, h, _J);

    return 0;
}

#define _HJ2 (3)
#define _WJ2 (2)
/**
 * XX
 * X
 * X
 */
static inline int tetris_J2_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WJ2) {
        return OUT_OF_BOUND;
    }

    /* Max height */
    h = t->h[x];
    if (t->h[x + 1] > 2 &&
        t->h[x + 1] - 2 > h) {
        h = t->h[x + 1] - 2;
    }

    if (h + _HJ2 > _H) {
        return OUT_OF_BOUND;
    }

    /* Update Height and Hole */
    t->h[x] = h + 3;
    t->h[x + 1] = t->h[x];

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h, _J);
    _SET(t, x, h - 1, _J);
    _SET(t, x, h - 2, _J);
    _SET(t, x + 1, h - 2, _J);

    return 0;
}

#define _HJ3 (2)
#define _WJ3 (3)
/**
 * XXX
 *   X
 */
static inline int tetris_J3_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WJ3) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x];
    if (t->h[x + 1] > h) {
        h = t->h[x + 1];
    }
    if (t->h[x + 2] + 1 > h) {
        h = t->h[x + 2] + 1;
    }

    if (h + _HJ3 > _H) {
        return OUT_OF_BOUND;
    }

    /* Update Height and Hole */
    t->h[x] = h + 1;
    t->h[x + 1] = h + 1;
    t->h[x + 2] = h + 1;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h, _J);
    _SET(t, x + 1, h, _J);
    _SET(t, x + 2, h, _J);
    _SET(t, x + 2, h + 1, _J);

    return 0;
}

#define _HJ4 (3)
#define _WJ4 (2)
/**
 *  X
 *  X
 * XX
 */
static inline int tetris_J4_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WJ4) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x];
    if (t->h[x + 1] > h) {
        h = t->h[x + 1];
    }

    if (h + _HJ4 > _H) {
        return OUT_OF_BOUND;
    }

    /* Update Height and Hole */
    t->h[x] = h + 1;
    t->h[x + 1] = h + 3;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h, _J);
    _SET(t, x + 1, h, _J);
    _SET(t, x + 1, h - 1, _J);
    _SET(t, x + 1, h - 2, _J);

    return 0;
}

static inline int tetris_J_push(tetris_t *t,
                                J_t       _j,
                                uint8_t   x)
{
    switch (_j) {
        case _J1: return tetris_J1_push(t, x);
        case _J2: return tetris_J2_push(t, x);
        case _J3: return tetris_J3_push(t, x);
        case _J4: return tetris_J4_push(t, x);
        default: return BAD_ITEM;
    }

    return 0;
}

#endif /* !TETRIS_J_H_ */
