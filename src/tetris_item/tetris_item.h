#ifndef TETRIS_ITEM_H_
# define TETRIS_ITEM_H_

#include "tetris.h"
#include "tetris_wall.h"

#define OUT_OF_BOUND (-1)
#define BAD_ITEM     (-2)

typedef int (*push_t)(tetris_t *, uint32_t, uint8_t);

/**
 * +---------+---------+---------+
 * | I: XXXX | L: XXX  | J: XXX  |
 * |         |      X  |    X    |
 * +---------+---------+---------+
 * | O:  XX  | S:  XX  | T:  X   |
 * |     XX  |    XX   |    XXX  |
 * +---------+---------+---------+
 * | Z: XX   |
 * |     XX  |
 * +---------+
 */
typedef enum {
    INIT_ITEM = 0,
    _I,
    _J,
    _L,
    _O,
    _S,
    _T,
    _Z,
} item_t;

/**
 * +------+------+
 * | I1   | I2   |
 * +------+------+
 * | XXXX | X    |
 * |      | X    |
 * |      | X    |
 * |      | X    |
 * +-------------+
 */
typedef enum {
    _I1 = 0,
    _I2,
    _INR,
} I_t;

/**
 * +-----+----+-----+----+
 * | L1  | L2 | L3  | L4 |
 * +-----+----+-----+----+
 * | X   | XX | XXX |  X |
 * | XXX | X  |   X |  X |
 * |     | X  |     | XX |
 * +----------+-----+----+
 */
typedef enum {
    _L1 = 0,
    _L2,
    _L3,
    _L4,
    _LNR,
} J_t;

/**
 * +-----+----+-----+----+
 * | J1  | J2 | J3  | J4 |
 * +-----+----+-----+----+
 * |   X | X  | XXX | XX |
 * | XXX | X  | X   |  X |
 * |     | XX |     |  X |
 * +----------+-----+----+
 */
typedef enum {
    _J1 = 0,
    _J2,
    _J3,
    _J4,
    _JNR,
} L_t;

/**
 * +----+
 * | O  |
 * +----+
 * | XX |
 * | XX |
 * +----+
 */
typedef enum {
    _O1 = 0,
    _ONR,
} O_t;

/**
 * +-----+----+
 * | S1  | S2 |
 * +-----+----+
 * |  XX | X  |
 * | XX  | XX |
 * |     |  X |
 * +----------+
 */
typedef enum {
    _S1 = 0,
    _S2,
    _SNR,
} S_t;

/**
 * +-----+----+-----+----+
 * | T1  | T2 | T3  | T4 |
 * +-----+----+-----+----+
 * |  X  | X  | XXX |  X |
 * | XXX | XX |  X  | XX |
 * |     | X  |     |  X |
 * +----------+-----+----+
 */
typedef enum {
    _T1 = 0,
    _T2,
    _T3,
    _T4,
    _TNR,
} T_t;

/**
 * +-----+----+
 * | Z1  | Z2 |
 * +-----+----+
 * | XX  |  X |
 * |  XX | XX |
 * |     | X  |
 * +----------+
 */
typedef enum {
    _Z1 = 0,
    _Z2,
    _ZNR,
} Z_t;

#include "tetris_I.h"
#include "tetris_J.h"
#include "tetris_L.h"
#include "tetris_O.h"
#include "tetris_S.h"
#include "tetris_T.h"
#include "tetris_Z.h"

static inline uint8_t tetris_item_nr_R_get(item_t item)
{
    switch (item) {
        case _I: return _INR;
        case _J: return _JNR;
        case _L: return _LNR;
        case _O: return _ONR;
        case _S: return _SNR;
        case _T: return _TNR;
        case _Z: return _ZNR;
        default: ;
    }

    return 0;
}

static inline push_t tetris_item_push_get(item_t item)
{
    switch (item) {
        case _I: return tetris_I_push;
        case _J: return tetris_J_push;
        case _L: return tetris_L_push;
        case _O: return tetris_O_push;
        case _S: return tetris_S_push;
        case _T: return tetris_T_push;
        case _Z: return tetris_Z_push;
        default: ;
    }

    return NULL;
}

#endif /* !TETRIS_ITEM_H_ */
