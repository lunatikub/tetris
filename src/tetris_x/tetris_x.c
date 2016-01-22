#include <curses.h>

#include "tetris_x.h"

#define SO (5) /* Start offset */
#define M  (3) /* Marge between cols */

int tetris_x_init()
{
    initscr();
    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);

    return 0;
}

static inline void I1_dump(int x, int y)
{
    mvprintw(y, x, "XXXX");
}

static inline void I2_dump(int x, int y)
{
    mvprintw(y, x, "X");
    mvprintw(y + 1, x, "X");
    mvprintw(y + 2, x, "X");
    mvprintw(y + 3, x, "X");
}

static inline void J1_dump(int x, int y)
{
    mvprintw(y, x, "X");
    mvprintw(y + 1, x, "XXX");
}

static inline void J2_dump(int x, int y)
{
    mvprintw(y, x, "XX");
    mvprintw(y + 1, x, "X");
    mvprintw(y + 2, x, "X");
}

static inline void J3_dump(int x, int y)
{
    mvprintw(y, x, "XXX");
    mvprintw(y + 1, x + 2, "X");
}

static inline void J4_dump(int x, int y)
{
    mvprintw(y, x + 1, "X");
    mvprintw(y + 1, x + 1, "X");
    mvprintw(y + 2, x, "XX");
}

static inline void L1_dump(int x, int y)
{
    mvprintw(y, x + 2, "X");
    mvprintw(y + 1, x, "XXX");
}

static inline void L2_dump(int x, int y)
{
    mvprintw(y, x, "X");
    mvprintw(y + 1, x, "X");
    mvprintw(y + 2, x, "XX");
}

static inline void L3_dump(int x, int y)
{
    mvprintw(y, x, "XXX");
    mvprintw(y + 1, x, "X");
}

static inline void L4_dump(int x, int y)
{
    mvprintw(y, x, "XX");
    mvprintw(y + 1, x + 1, "X");
    mvprintw(y + 2, x + 1, "X");
}


static inline void O1_dump(int x, int y)
{
    mvprintw(y, x, "XX");
    mvprintw(y + 1, x, "XX");
}

static inline void S1_dump(int x, int y)
{
    mvprintw(y, x + 1, "XX");
    mvprintw(y + 1, x, "XX");
}

static inline void S2_dump(int x, int y)
{
    mvprintw(y, x, "X");
    mvprintw(y + 1, x, "XX");
    mvprintw(y + 2, x + 1, "X");
}

static inline void T1_dump(int x, int y)
{
    mvprintw(y, x + 1, "X");
    mvprintw(y + 1, x, "XXX");
}

static inline void T2_dump(int x, int y)
{
    mvprintw(y, x, "X");
    mvprintw(y + 1, x, "XX");
    mvprintw(y + 2, x, "X");
}

static inline void T3_dump(int x, int y)
{
    mvprintw(y, x, "XXX");
    mvprintw(y + 1, x + 1, "X");
}

static inline void T4_dump(int x, int y)
{
    mvprintw(y, x + 1, "X");
    mvprintw(y + 1, x, "XX");
    mvprintw(y + 2, x + 1, "X");
}

static inline void Z1_dump(int x, int y)
{
    mvprintw(y, x, "XX");
    mvprintw(y + 1, x + 1, "XX");
}

static inline void Z2_dump(int x, int y)
{
    mvprintw(y, x + 1, "X");
    mvprintw(y + 1, x, "XX");
    mvprintw(y + 2, x, "X");
}

static inline char item2char(item_t item)
{
    switch (item) {
        case _I: return 'I';
        case _J: return 'J';
        case _L: return 'L';
        case _O: return 'O';
        case _S: return 'S';
        case _T: return 'T';
        case _Z: return 'Z';
        default: return '.';
    };

    return '.';
}

static inline int item2color(item_t item)
{
    switch (item) {
        case _I: return 1;
        case _J: return 2;
        case _L: return 3;
        case _O: return 4;
        case _S: return 5;
        case _T: return 6;
        case _Z: return 7;
        default: return 0;
    };

    return '.';
}

#define SOX_EVAL (75)
#define SOY_EVAL (2)

#define _XM (25)
#define _YM (28)

static uint32_t _n = 0;

void tetris_x_eval_init(void)
{
    _n = 0;
}

void tetris_x_eval_dump(tetris_t *t,
                        uint8_t   _x,
                        uint8_t   r,
                        double    score)
{
    uint8_t xm = (_n) % 4;
    uint8_t ym = ((_n) / 4) % 2;

    mvprintw(SOY_EVAL + ym * _YM, SOX_EVAL + xm * _XM,
             "x:%u r:%u", _x, r);

    mvprintw(SOY_EVAL + ym * _YM + 1, SOX_EVAL + xm * _XM,
             "l:%-2i e:%-2i dr: %-2i dc:%-2i",
             t->_e.l, t->_e.e, t->_e.dr, t->_e.dc);

    mvprintw(SOY_EVAL + ym * _YM + 2, SOX_EVAL + xm * _XM,
             "L:%-2i W:%-2i R:%-2i",
             t->_e.L, t->_e.W, t->_e.R);

    mvprintw(SOY_EVAL + ym * _YM + 3, SOX_EVAL + xm * _XM,
             "%f", score);

    uint8_t x = 0;
    uint8_t y = 0;

    for (x = 0; x < _W; ++x) {
        for (y = 0; y < _H; ++y) {
            char c = _GET(t, x, y) ? 'X' : '.';
            mvprintw(SOY_EVAL + ym * _YM + 4 + y, SOX_EVAL + xm * _XM + x,
                     "%c", c);
        }
    }

    refresh();
    ++_n;
}

void tetris_x_score_dump(tetris_t *t,
                         uint8_t   _x,
                         uint8_t   _r,
                         double    score)
{
    mvprintw(10, 45, "Best Score: %f", score);
    mvprintw(11, 45, "x: %u r: %u", _x, _r);

    uint8_t x = 0;
    uint8_t y = 0;

    for (x = 0; x < _W; ++x) {
        for (y = 0; y < _H; ++y) {
            char c = _GET(t, x, y) ? 'X' : '.';
            mvprintw(12 + y, 45 + x, "%c", c);
        }
    }
}

void tetris_x_main_dump(tetris_t *t,
                        item_t    item)
{
    uint32_t x = 0;
    uint32_t y = 0;

    for (y = 0; y < _H; ++y) {
        mvprintw(y + SO, 0, "%2u|", _H - y - 1);
        mvprintw(y + SO, _W * M + M + 1, "|");
    }

    for (x = 0; x < _W; ++x) {
        mvprintw(_H + SO + 1, x * M + SO, "%u", x);
        mvprintw(_H + SO, x * M + SO, "__");
    }

    for (x = 0; x < _W; ++x) {
        for (y = 0; y < _H; ++y) {
            char c = item2char(_GET(t, x, y));
            int color = item2color(_GET(t, x, y));

            attron(COLOR_PAIR(color));
            mvprintw(y + SO, x * M + SO, "%c", c);
            attroff(COLOR_PAIR(color));
        }
    }

    for (y = 0; y < _H; ++y) {
        mvprintw(y + SO, _W * M + SO + 1, "[%2u]", t->n[y]);
    }

    mvprintw(_H + 3 + SO, _W * M + SO, "height");
    mvprintw(_H + 4 + SO, _W * M + SO, "hole");

    for (x = 0; x < _W; ++x) {
        mvprintw(_H + 3 + SO, x * M + SO, "%-2u", t->h[x]);
        mvprintw(_H + 4 + SO, x * M + SO, "%-2u", t->hole[x]);
    }

    mvprintw(SO, _W * M + 3 * SO , "next item: [%c]", item2char(item));
    mvprintw(SO + 1, _W * M + 3 * SO, "nr_line:   [%10u]", t->nr_completed);

    refresh();
}

int tetris_x_clean()
{
    endwin();
    return 0;
}
