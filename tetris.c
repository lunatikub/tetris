#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "tetris.h"
#include "tetris_abstraction.h"
#include "tetris_ia.h"
#include "tetris_map.h"

static inline int tetris_init(tetris_t *t)
{
    memset(t->map, 0, _W * _H * sizeof(uint8_t));
    memset(t->h, 0, _W * sizeof(uint8_t));
    memset(t->hole, 0, _W * sizeof(uint8_t));
    memset(t->n, 0, _H * sizeof(uint8_t));
    t->nr = 0;

    if (tetris_abstraction_init()) {
        return -1;
    }
    return 0;
}

static inline int tetris_clean(tetris_t *t)
{
    (void)t;

    if (tetris_abstraction_clean()) {
        return -1;
    }
    return 0;
}

static inline void tetris_check_h(tetris_t *t)
{
    uint8_t x = 0;
    uint8_t y = 0;

    uint8_t h = 0;

    for (x = 0; x < _W; ++x) {
        h = t->h[x];
        y = 0;
        while (y < _H && _GET(t->map, x, y) == 0) {
            ++y;
        }
        if (_H - y != h) {
            fprintf(stderr, " bad h: %u expected: %u\n", _H - y, h);
            tetris_emul_dump(t, 0, 0);
            getchar();
            abort();
        }
    }
}

int main(void)
{
    tetris_t t;
    move_t   m;

    item_t item = INIT_ITEM;

    if (tetris_init(&t)) {
        TETRIS_ERR("Init");
    }

    /* tetris_I_push(&t, _I1, 0); */
    /* tetris_Z_push(&t, _Z1, 3); */
    /* tetris_emul_dump(&t, item, 0); */
    /* getchar(); */
    /* return 0; */

    for (;;) {
        item  = tetris_emul_next_item_get();
        tetris_emul_dump(&t, item, 0);
        /* tetris_emul_game(&t, item); */
        tetris_next_move_get(&t, item, &m);
        m.p(&t, m.r, m.x);
        tetris_hole_update(&t);
        tetris_map_update(&t);
        tetris_check_h(&t);
        usleep(100000);
    }

    if (tetris_clean(&t)) {
        return 1;
    }

    return 0;
}
