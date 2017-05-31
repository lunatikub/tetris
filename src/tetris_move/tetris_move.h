#ifndef TETRIS_MOVE_H_
# define TETRIS_MOVE_H_

#define MAX_KEYS_SZ (16)

typedef struct {
    uint8_t hold;
    int8_t  x;
    int8_t  r;
} move_t;

void tetris_move2keys(item_t  item,
                      move_t *mv,
                      int    *k,
                      int    *nr);

#endif /* !TETRIS_MOVE_H_ */
