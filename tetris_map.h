#ifndef TETRIS_MAP_H_
# define TETRIS_MAP_H_

static inline int tetris_hole_update(tetris_t *t)
{
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t nr = 0;

    for (x = 0; x < _W; ++x) {
        y = 0;
        nr = 0;
        while (y < _H && _GET(t->map, x, y) == 0) {
            ++y;
        }
        while (y < _H) {
            if (_GET(t->map, x, y) == 0) {
                ++nr;
            }
            ++y;
        }
        t->hole[x] = nr;
    }

    return 0;
}

static inline void tetris_clear_line(tetris_t *t,
                                     uint8_t   n)
{
    uint8_t x = 0;
    uint8_t y = 0;

    memmove(&t->map[_W], &t->map[0], n * _W);
    memset(&t->map[0], 0, _W);
    for (x = 0; x < _W; ++x) {
        y = 0;
        while (y < _H && _GET(t->map, x, y) == 0) {
            ++y;
        }
        t->h[x] = _H - y;
    }
    memmove(&t->n[1], &t->n[0], n);
    t->n[0] = 0;
    ++t->nr;
}

static inline int tetris_map_update(tetris_t *t)
{
    uint8_t n = 0;

    for (n = 0; n < _H; ++n) {
        if (t->n[n] == 10) {
            tetris_clear_line(t, n);
        }
    }

    return 0;
}

#endif /* !TETRIS_MAP_H_ */
