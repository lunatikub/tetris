#ifndef TETRIS_L_H_
# define TETRIS_L_H_

#define _HL1 (2)
#define _WL1 (3)
/**
 * X
 * XXX
 */
static inline int tetris_L1_push(tetris_t *t,
                                  uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WL1) {
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

    if (h + _HL1 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HL1;

    /* Update Height and Hole */
    t->h[x] = h + 2;
    t->h[x + 1] = h + 1;
    t->h[x + 2] = h + 1;

    h = _H - h - 1;

    /* Update the wall*/
    _SET(t, x, h, _L);
    _SET(t, x, h - 1, _L);
    _SET(t, x + 1, h, _L);
    _SET(t, x + 2, h, _L);

    return 0;
}

#define _HL2 (3)
#define _WL2 (2)
/**
 * XX
 * X
 * X
 */
static inline int tetris_L2_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WL2) {
        return OUT_OF_BOUND;
    }

    /* Max height */
    h = t->h[x];
    if (t->h[x + 1] > 2 &&
        t->h[x + 1] - 2 > h) {
        h = t->h[x + 1] - 2;
    }

    if (h + _HL2 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HL2;

    /* Update Height and Hole */
    t->h[x] = h + 3;
    t->h[x + 1] = t->h[x];

    h = _H - h - 1;

    /* Update the wall*/
    _SET(t, x, h, _L);
    _SET(t, x, h - 1, _L);
    _SET(t, x, h - 2, _L);
    _SET(t, x + 1, h - 2, _L);

    return 0;
}

#define _HL3 (2)
#define _WL3 (3)
/**
 * XXX
 *   X
 */
static inline int tetris_L3_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WL3) {
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

    if (h + _HL3 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + 1;

    /* Update Height and Hole */
    t->h[x] = h + 1;
    t->h[x + 1] = h + 1;
    t->h[x + 2] = h + 1;

    h = _H - h - 1;

    /* Update the wall*/
    _SET(t, x, h, _L);
    _SET(t, x + 1, h, _L);
    _SET(t, x + 2, h, _L);
    _SET(t, x + 2, h + 1, _L);

    return 0;
}

#define _HL4 (3)
#define _WL4 (2)
/**
 *  X
 *  X
 * XX
 */
static inline int tetris_L4_push(tetris_t *t,
                                 uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WL4) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x];
    if (t->h[x + 1] > h) {
        h = t->h[x + 1];
    }

    if (h + _HL4 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HL4;

    /* Update Height and Hole */
    t->h[x] = h + 1;
    t->h[x + 1] = h + 3;

    h = _H - h - 1;

    /* Update the wall*/
    _SET(t, x, h, _L);
    _SET(t, x + 1, h, _L);
    _SET(t, x + 1, h - 1, _L);
    _SET(t, x + 1, h - 2, _L);

    return 0;
}

static inline int tetris_L_push(tetris_t *t,
                                L_t       _j,
                                uint8_t   x)
{
    switch (_j) {
        case _L1: return tetris_L1_push(t, x);
        case _L2: return tetris_L2_push(t, x);
        case _L3: return tetris_L3_push(t, x);
        case _L4: return tetris_L4_push(t, x);
        default: return BAD_ITEM;
    }

    return 0;
}

#endif /* !TETRIS_L_H_ */
