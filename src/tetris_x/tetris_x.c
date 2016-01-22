#include <curses.h>

#include "tetris_wall.h"
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

static inline void I_dump(int x, int y)
{
    mvprintw(y, x, "XXXX");
}

static inline void J_dump(int x, int y)
{
    mvprintw(y, x, "X");
    mvprintw(y + 1, x, "XXX");
}

static inline void L_dump(int x, int y)
{
    mvprintw(y, x + 2, "X");
    mvprintw(y + 1, x, "XXX");
}

static inline void O_dump(int x, int y)
{
    mvprintw(y, x, "XX");
    mvprintw(y + 1, x, "XX");
}

static inline void S_dump(int x, int y)
{
    mvprintw(y, x + 1, "XX");
    mvprintw(y + 1, x, "XX");
}

static inline void T_dump(int x, int y)
{
    mvprintw(y, x + 1, "X");
    mvprintw(y + 1, x, "XXX");
}

static inline void Z_dump(int x, int y)
{
    mvprintw(y, x, "XX");
    mvprintw(y + 1, x + 1, "XX");
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

#define _XM (12)
#define _YM (23)

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
    uint8_t xm = (_n) % 9;
    uint8_t ym = ((_n) / 9) % 2;

    mvprintw(SOY_EVAL + ym * _YM, SOX_EVAL + xm * _XM,
             "x:%u r:%u", _x, r);

    mvprintw(SOY_EVAL + ym * _YM + 1, SOX_EVAL + xm * _XM,
             "%.4f", score);

    uint8_t x = 0;
    uint8_t y = 0;

    for (x = 0; x < _W; ++x) {
        for (y = 0; y < _H; ++y) {
            char c = _GET(t, x, y) ? 'X' : '.';
            mvprintw(SOY_EVAL + ym * _YM + 2 + y, SOX_EVAL + xm * _XM + x,
                     "%c", c);
        }
    }

    refresh();
    if (_D_ == 2) {
        getchar();
    }
    ++_n;
}

void tetris_x_score_dump(tetris_t *t,
                         uint8_t   _x,
                         uint8_t   _r,
                         double    score)
{
    mvprintw(0, 45, "- Best Wall -", score);
    mvprintw(1, 45, "%.4f", score);
    mvprintw(2, 45, "x: %u r: %u", _x, _r);

    uint8_t x = 0;
    uint8_t y = 0;

    for (x = 0; x < _W; ++x) {
        for (y = 0; y < _H; ++y) {
            char c = _GET(t, x, y) ? 'X' : '.';
            mvprintw(3 + y, 45 + x, "%c", c);
        }
    }
}

static inline void tetris_x_item_dump(item_t  item,
                                      uint8_t x,
                                      uint8_t y)
{
    int color = item2color(item);

    uint8_t _x = 0;
    uint8_t _y = 0;

    for (_x = x; _x < x + 8; ++_x) {
        for (_y = y; _y < y + 6; ++_y) {
            mvprintw(_y, _x, " ");
        }
    }

    mvprintw(y, x, "+-----+");
    mvprintw(y + 1, x, "|");
    mvprintw(y + 1, x + 6, "|");
    mvprintw(y + 2, x, "|");
    mvprintw(y + 2, x + 6, "|");
    mvprintw(y + 3, x, "|");
    mvprintw(y + 3, x + 6, "|");
    mvprintw(y + 4, x, "|");
    mvprintw(y + 4, x + 6, "|");
    mvprintw(y + 5, x, "+-----+");

    attron(COLOR_PAIR(color));
    switch(item) {
        case _I: I_dump(x + 1, y + 1); break;
        case _J: J_dump(x + 1, y + 1); break;
        case _L: L_dump(x + 1, y + 1); break;
        case _O: O_dump(x + 1, y + 1); break;
        case _S: S_dump(x + 1, y + 1); break;
        case _T: T_dump(x + 1, y + 1); break;
        case _Z: Z_dump(x + 1, y + 1); break;
        default: ;
    }
    attroff(COLOR_PAIR(color));
}

static inline void tetris_x_items_dump(item_t  curr_item,
                                       item_t  hold_item,
                                       item_t *items)
{
    uint32_t i = 0;

    tetris_x_item_dump(curr_item, 2, 32);
    tetris_x_item_dump(hold_item, 10, 32);

    for (i = 0; i < _ITEM; ++i) {
        tetris_x_item_dump(items[i], 2 + i * 6, 38);
    }
}

void tetris_x_main_dump(tetris_t *t,
                        item_t    curr_item,
                        item_t   *items)
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

    mvprintw(1, 1, "nr_line:   [%10u]", t->nr_completed);
    mvprintw(2, 1, "nr_hold:   [%10u]", t->nr_hold);
    mvprintw(3, 1, "nr_items:  [%10u]", t->nr_items);

    tetris_x_items_dump(curr_item, t->hold, items);

    refresh();
    if (_D_) {
        getchar();
    }
}

int tetris_x_clean()
{
    endwin();
    return 0;
}
