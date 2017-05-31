#include <stdint.h>

#include "tetris_item.h"
#include "tetris_move.h"
#include "tetris_x11_keyboard.h"

static uint8_t _Ioff[_INR] = { 3, 5 };
static uint8_t _Joff[_JNR] = { 3, 4, 3, 3 };
static uint8_t _Loff[_LNR] = { 3, 4, 3, 3 };
static uint8_t _Ooff[_ONR] = { 4 };
static uint8_t _Soff[_SNR] = { 3, 3 };
static uint8_t _Toff[_TNR] = { 3, 4, 4, 3 };
static uint8_t _Zoff[_ZNR] = { 3, 4 };

static inline void tetris_move2keys_r(int8_t  r,
                                      int    *k,
                                      int    *nr)
{
    uint8_t i = 0;

    for (i = *nr; i < *nr + r; ++i) {
        k[i] = K_ROT;
    }

    *nr += r;
}

static inline void tetris_move2keys_x(item_t  item,
                                      int8_t  r,
                                      int8_t  x,
                                      int    *k,
                                      int    *nr)
{
    uint8_t i  = 0;
    int8_t  xs = 0; /* x offset start */

    switch (item) {
        case _I: xs = _Ioff[r]; break;
        case _J: xs = _Joff[r]; break;
        case _L: xs = _Loff[r]; break;
        case _O: xs = _Ooff[r]; break;
        case _S: xs = _Soff[r]; break;
        case _T: xs = _Toff[r]; break;
        case _Z: xs = _Zoff[r]; break;
        default: xs = 0;
    }

    uint32_t key = (xs > x) ? K_LEFT : K_RIGHT;
    uint8_t  d = abs(xs - x);

    for (i = *nr; i < d + *nr; ++i) {
        k[i] = key;
    }

    *nr += d;
}

void tetris_move2keys(item_t  item,
                      move_t *mv,
                      int    *k,
                      int    *nr)
{
    if (mv->hold) {
        k[0] = K_HOLD;
        ++(*nr);
        return;
    }

    tetris_move2keys_r(mv->r, k, nr);
    tetris_move2keys_x(item, mv->r, mv->x, k, nr);

    k[*nr] = K_DROP;
    ++(*nr);
}
