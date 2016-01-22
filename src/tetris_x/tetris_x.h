#ifndef TETRIS_X_H_
# define TETRIS_X_H_

#include "tetris_item.h"
#include "tetris_ia.h"

int tetris_x_init();

int tetris_x_clean();

item_t tetris_x_next_item_get();

void tetris_x_main_dump(tetris_t *t,
                        item_t    item);

void tetris_x_eval_dump(tetris_t *t,
                        uint8_t   _x,
                        uint8_t   r,
                        double    score);

void tetris_x_eval_init(void);

void tetris_x_score_dump(tetris_t *t,
                         uint8_t   x,
                         uint8_t   r,
                         double    score);

#endif /* !TETRIS_X_H_ */
