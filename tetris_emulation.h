#ifndef TETRIS_EMULATION_H_
# define TETRIS_EMULATION_H_

#include <stdint.h>

#include "tetris_item.h"

int tetris_emul_init(void);
item_t tetris_emul_next_item_get(void);
int tetris_emul_clean(void);

void tetris_emul_dump(tetris_t *t, item_t item, uint32_t score);

void tetris_emul_game(tetris_t *t,
                      item_t    item);

#endif /* !TETRIS_EMULATION_H_ */
