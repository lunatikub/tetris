#ifndef TETRIS_WALL_H_
# define TETRIS_WALL_H_

#include "tetris.h"

#define _GET(t,x,y) ((t)->wall[((y) * _W) + (x)])

#define _SET(t,x,y,I)                           \
    ({                                          \
        ((t)->wall[((y) * _W) + (x)] = I);      \
        ((t)->n[y]++);                          \
    })

/**
 * Update the number of holes
 * Clear completed lines.
 */
void tetris_wall_update(tetris_t *t);

#endif /* !TETRIS_WALL_H_ */
