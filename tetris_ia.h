#ifndef TETRIS_IA_H_
# define TETRIS_IA_H_

#include <stdint.h>

#include "tetris.h"
#include "tetris_item.h"

typedef struct {
    uint8_t r;
    uint8_t x;
    push_t  p;
} move_t;

void tetris_next_move_get(tetris_t *t,
                          item_t    item,
                          move_t   *move);

#endif /* !TETRIS_IA_H_ */
