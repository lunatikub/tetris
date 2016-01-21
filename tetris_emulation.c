#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "tetris.h"
#include "tetris_emulation.h"

int tetris_emul_init(void)
{
    srand(time(NULL));
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

item_t tetris_emul_next_item_get(void)
{
    return rand() % _Z + 1;
}

#define SO (5) /* Start offset */
#define M  (3) /* Marge between cols */

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

void tetris_emul_game_clean(int x, int y)
{
    mvprintw(y, x,     "                                   ");
    mvprintw(y + 1, x, "                                   ");
    mvprintw(y + 2, x, "                                   ");
    mvprintw(y + 3, x, "                                   ");
}

void tetris_emul_game(tetris_t *t,
                      item_t    item)
{
    int x = _W * M + 3 * SO;
    int y = SO + 3;

    mvprintw(y, x, "Rotation:?");

    switch (item) {
        case _I:
            I1_dump(x + 11, y);
            I2_dump(x + 16, y);
            break;
        case _J:
            J1_dump(x + 11, y);
            J2_dump(x + 16, y);
            J3_dump(x + 21, y);
            J4_dump(x + 26, y);
            break;
        case _L:
            L1_dump(x + 11, y);
            L2_dump(x + 16, y);
            L3_dump(x + 21, y);
            L4_dump(x + 26, y);
            break;
        case _O:
            O1_dump(x + 11, y);
            break;
        case _S:
            S1_dump(x + 11, y);
            S2_dump(x + 16, y);
            break;
        case _T:
            T1_dump(x + 11, y);
            T2_dump(x + 16, y);
            T3_dump(x + 21, y);
            T4_dump(x + 26, y);
            break;
        case _Z:
            Z1_dump(x + 11, y);
            Z2_dump(x + 16, y);
            break;
        default:
                break;
    }

    int _r = getch() - '0';

    tetris_emul_game_clean(x, y);

    mvprintw(y, x, "Col:?");

    int _x = getch() - '0';

    tetris_emul_game_clean(x, y);

    switch (item) {
        case _I: tetris_I_push(t, _r, _x); break;
        case _J: tetris_J_push(t, _r, _x); break;
        case _L: tetris_L_push(t, _r, _x); break;
        case _O: tetris_O_push(t, _r, _x); break;
        case _S: tetris_S_push(t, _r, _x); break;
        case _T: tetris_T_push(t, _r, _x); break;
        case _Z: tetris_Z_push(t, _r, _x); break;
        default:;
    }

    refresh();
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
void tetris_emul_dump(tetris_t *t,
                      item_t    item,
                      uint32_t  score)
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
            char c = item2char(_GET(t->map, x, y));
            int color = item2color(_GET(t->map, x, y));

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
    mvprintw(SO + 1, _W * M + 3 * SO, "score:     [%4u]", score);
    mvprintw(SO + 2, _W * M + 3 * SO, "nr_line:   [%4u]", t->nr);

    refresh();
}

int tetris_emul_clean(void)
{
    endwin();
    return 0;
}
