#ifndef TETRIS_H_
# define TETRIS_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define _X_ (0)
/**
 * LELVE 0 --> No pause.
 * LEVEL 1 --> Pause at 'main_dump'.
 * LEVEL 2 --> Pause at 'main_dump' and 'eval_dump'.
 * LEVEL 3 --> Pause at 'main_dump' and wait 100ms 'eval_dump'
 */
#define _D_ (0)

/**
 * Configuration
 */
#define _ITEM (5)
#define _W    (10)
#define _H    (20)

typedef struct {
    uint8_t hold;
    int8_t  x;
    int8_t  r;
} move_t;

typedef struct {
    int l;  /* Last item height. */
    int e;  /* Number of cleared lines with the last item. */
    int dr; /* Number of transitions between full/empty cell for each lines. */
    int dc; /* Number of transitions between full/empty cell for each cols. */
    int L;  /* Number of holes. */
    int W;  /* Depth of wells. */
    int R;  /* Number of lines with at least a hole (NOT USED). */
} eval_t;

typedef struct {
    uint8_t  wall[_W * _H];     /* Wall. */
    uint8_t  h[_W];             /* Height of a col. */
    uint8_t  hole[_W];          /* Number of holes by col. */
    uint8_t  n[_H];             /* Number of cells by line. */
    uint8_t  nr_last_completed; /* Number of completed lines from the last move. */
    uint32_t nr_completed;      /* Number of completed lines. */
    uint32_t nr_items;          /* Number of items played. */
    eval_t   _e;                /* Current evaluation of the wall. */
    uint8_t  hold;              /* Hold item. */
    uint32_t nr_hold;           /* Number of hold switchs. */
    double   score;             /* Current score of the Wall. */
} tetris_t;

#endif /* !TETRIS_H_ */
