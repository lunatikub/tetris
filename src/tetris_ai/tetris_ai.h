#ifndef TETRIS_AI_H_
# define TETRIS_AI_H_

#include <stdint.h>

#include "tetris.h"
#include "tetris_item.h"
#include "tetris_move.h"

int tetris_ai(tetris_t *t,
              item_t    curr_item,
              item_t   *items,
              move_t   *mv);

void tetris_eval(tetris_t *t);

#endif /* !TETRIS_AI_H_ */
