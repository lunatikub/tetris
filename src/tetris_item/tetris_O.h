#ifndef TETRIS_O_H_
# define TETRIS_O_H_

#define _HO1 (2)
#define _WO1 (2)
/**
 * XX
 * XX
 */
static inline int tetris_01_push(tetris_t *t,
                                  uint8_t   x)
{
    uint8_t h = 0;

    if (x > _W - _WO1) {
        return OUT_OF_BOUND;
    }

    /* height detection */
    h = t->h[x];
    if (t->h[x + 1] > h) {
        h = t->h[x + 1];
    }

    if (h + _HO1 > _H) {
        return OUT_OF_BOUND;
    }

    t->_e.l = h + _HO1;

    /* Update Height and Hole */
    t->h[x] = h + 2;
    t->h[x + 1] = h + 2;

    h = _H - h - 1;

    /* Update the map */
    _SET(t, x, h, _O);
    _SET(t, x, h - 1, _O);
    _SET(t, x + 1, h, _O);
    _SET(t, x + 1, h - 1, _O);

    return 0;
}

static inline int tetris_O_push(tetris_t *t,
                                O_t       _o,
                                uint8_t   x)
{
    switch (_o) {
        case _O1: return tetris_01_push(t, x);
        default: return BAD_ITEM;
    }

    return 0;
}

#endif /* !TETRIS_O_H_ */
