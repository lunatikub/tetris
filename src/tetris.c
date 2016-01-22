#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "tetris.h"
#include "tetris_ai.h"
#include "tetris_map.h"
#include "tetris_x.h"

static inline item_t tetris_emul_next_item_get(void)
{
    static item_t last_item = INIT_ITEM;
    item_t item = rand() % _Z + 1;

    while (item == last_item) {
        item = rand() % _Z + 1;
    }
    last_item = item;

    return item;
}

static inline int tetris_init(tetris_t *t)
{
    memset(t->map, 0, _W * _H * sizeof(uint8_t));
    memset(t->h, 0, _W * sizeof(uint8_t));
    memset(t->hole, 0, _W * sizeof(uint8_t));
    memset(t->n, 0, _H * sizeof(uint8_t));
    t->nr_completed = 0;
    t->nr_last_completed = 0;

    srand(time(NULL));

    if (_X_ && tetris_x_init()) {
        return -1;
    }

    return 0;
}

static inline int tetris_clean(tetris_t *t)
{
    (void)t;

    if (_X_ && tetris_x_clean()) {
        return -1;
    }

    return 0;
}

int main(void)
{
    tetris_t t;

    item_t item = INIT_ITEM;

    if (tetris_init(&t)) {
        TETRIS_ERR("Init");
    }

    for (;;) {
        item  = tetris_emul_next_item_get();
        if (_X_) {
            tetris_x_main_dump(&t, item);
        }
        /* tetris_emul_game(&t, item); */
        if (tetris_ai(&t, item)) {
            break;
        }
        tetris_map_update(&t);
    }

    if (tetris_clean(&t)) {
        return 1;
    }

    if (_X_ == 0) {
        printf("%u\n", t.nr_completed);
    }

    return 0;
}
