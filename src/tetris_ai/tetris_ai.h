#ifndef TETRIS_AI_H_
# define TETRIS_AI_H_

#include <stdint.h>

#include "tetris.h"
#include "tetris_item.h"

typedef struct {
    uint8_t r;
    uint8_t x;
    push_t  p;
} move_t;

int tetris_ai(tetris_t *t,
              item_t    item);

double tetris_score_get(tetris_t *t);

#endif /* !TETRIS_AI_H_ */
