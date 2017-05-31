#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>

#include "tetris_x11.h"

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

static inline int tetris_x11_simulation_init(tetris_x11_t *t11,
                                             item_t       *items)
{
    int    n    = 0;
    rgb_t  rgb  = { 0, 0, 0 };

    for (n = 0; n < _ITEM; ++n) {

        tetris_x11_block_color_get(t11->d,
                                   t11->c[n].x[_UL], t11->c[n].x[_DR],
                                   t11->c[n].y[_UL], t11->c[n].y[_DR],
                                   &rgb);

        items[n] = tetris_x11_item_find(t11, &rgb, n);
        mvprintw(n, 0, "%c", item2char(items[n]));
    }
    refresh();

    return 0;
}

static inline int tetris_x11_simulation(tetris_x11_t *t11,
                                        item_t       *items)
{
    rgb_t  rgb = { 0, 0, 0 };
    item_t it  = INIT_ITEM;

    erase();

    int i = 0;
    int n = 0;

    for (i = 0; i < 20000; ++i) {

        tetris_x11_block_color_get(t11->d,
                                   t11->c[4].x[_UL], t11->c[4].x[_DR],
                                   t11->c[4].y[_UL], t11->c[4].y[_DR],
                                   &rgb);

        it = tetris_x11_item_find(t11, &rgb, 4);

        if (it != items[4]) {
            items[0] = items[1];
            items[1] = items[2];
            items[2] = items[3];
            items[3] = items[4];
            items[4] = it;
        }

        mvprintw(0, 5, "%u/2000", i);
        for (n = 0; n < _ITEM; ++n) {
            mvprintw(n, 0, "%c", item2char(items[n]));
        }
        refresh();
        usleep(200000);
    }

    return 0;
}

int main(int argc, char **argv)
{
    tetris_x11_t t11;

    item_t items[_ITEM] = { INIT_ITEM };

    FILE *cfg = NULL;

    int i = 0;

    if (argc != 2) {
        fprintf(stderr, "./tetris_x11_simulation config\n");
        return -1;
    }

    if ((cfg = fopen(argv[1], "r")) == NULL) {
        return -1;
    }

    tetris_x11_init(&t11);
    tetris_x11_config_load(&t11, cfg);

    printf("Simulation will begin in \n");
    for (i = 0; i < 3; ++i) {
        printf("%u/%u\r", i, 3);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");

    initscr();

    while (1) {
        tetris_x11_simulation_init(&t11, items);
        mvprintw(8, 0, "OK ? (Y/N)");
        char c  = getchar();

        if (c == 'Y') {
            break;
        }
    }

    tetris_x11_simulation(&t11, items);

    tetris_x11_clean(&t11);

    endwin();

    fclose(cfg);

    return 0;
}
