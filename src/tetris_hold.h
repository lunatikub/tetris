#ifndef TETRIS_HOLD_H_
# define TETRIS_HOLD_H_

static inline tetris_hold_set(tetris_t *t,
                              item_t    item)
{
    ++t->nr_hold;
    t->hold = item;
}

static inline tetris_hold_is_empty(tetris_t *t)
{
    return (t->hold == 0) ? 1 : 0;
}

#endif /* !TETRIS_HOLD_H_ */
