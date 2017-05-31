#include <string.h>

#include "tetris_wall.h"

static inline int tetris_hole_update(tetris_t *t)
{
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t nr = 0;

    for (x = 0; x < _W; ++x) {
        y = 0;
        nr = 0;
        while (y < _H && _GET(t, x, y) == 0) {
            ++y;
        }
        while (y < _H) {
            if (_GET(t, x, y) == 0) {
                ++nr;
            }
            ++y;
        }
        t->hole[x] = nr;
    }

    return 0;
}

static inline void tetris_completed_line_update(tetris_t *t,
                                                uint8_t   n)
{
    uint8_t x = 0;
    uint8_t y = 0;

    memmove(&t->wall[_W], &t->wall[0], n * _W);
    memset(&t->wall[0], 0, _W);
    for (x = 0; x < _W; ++x) {
        y = 0;
        while (y < _H && _GET(t, x, y) == 0) {
            ++y;
        }
        t->h[x] = _H - y;
    }
    memmove(&t->n[1], &t->n[0], n);
    t->n[0] = 0;
}

void tetris_wall_update(tetris_t *t)
{
    uint8_t n = 0;

    t->nr_last_completed = 0;

    tetris_hole_update(t);

    for (n = 0; n < _H; ++n) {
        if (t->n[n] == _W) {
            tetris_completed_line_update(t, n);
            ++t->nr_completed;
            ++t->nr_last_completed;
        }
    }
}
