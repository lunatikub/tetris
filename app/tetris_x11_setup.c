#include <unistd.h>
#include <stdio.h>

#include "tetris_x11.h"

static inline void tetris_x11_coord_get(tetris_x11_t *t11,
                                        const char   *msg,
                                        int          *x,
                                        int          *y)
{
    Window w = XRootWindow(t11->d, DefaultScreen(t11->d));
    XEvent xevent;

    printf("%s\n", msg);

    while(1) {
        XGrabPointer(t11->d, w, True,
                     PointerMotionMask | ButtonPressMask | ButtonReleaseMask,
                     GrabModeAsync, GrabModeAsync,
                     None, None, CurrentTime);

        XAllowEvents(t11->d, AsyncPointer, CurrentTime);
        XNextEvent(t11->d, &xevent);

        switch (xevent.type) {
            case ButtonPress:{
                /* Mouse left click */
                if (xevent.xbutton.button == 1) {
                    goto clicked;
                }
            }
            default:
                ;
        }
    }
  clicked:
    XUngrabPointer(t11->d,CurrentTime);

    *x = xevent.xbutton.x_root;
    *y = xevent.xbutton.y_root;
}

static inline int tetris_x11_setup_citem2idx(char item)
{
    switch (item) {
        case 'I': return 0;
        case 'J': return 1;
        case 'L': return 2;
        case 'O': return 3;
        case 'S': return 4;
        case 'T': return 5;
        case 'Z': return 6;
    }

    return 0;
}

static inline int tetris_x11_setup(tetris_x11_t *t11)
{
    int i = 0;

    printf("Setup will begin in \n");
    for (i = 0; i < 3; ++i) {
        printf("%u/%u\r", i, 3);
        fflush(stdout);
        sleep(1);
    }
    printf("\n\n");

    int n = 0; /* item number */
    int c = 0; /* corner */

    char msg[256] = {};

    tetris_x11_coord_get(t11, "WIND\n", &t11->c[0].x[0], &t11->c[0].y[0]);

    for (n = 0; n < _ITEM; ++n) {
        for (c = 0; c < _NRC; ++c) {
            sprintf(msg, "<%s %u> ", (c == _UL) ? "up left" : "down right", n + 1);
            tetris_x11_coord_get(t11, msg, &t11->c[n].x[c], &t11->c[n].y[c]);
            printf("[%u][%u] %u %u\n", n, c, t11->c[n].x[c], t11->c[n].y[c]);
        }
        printf("\n");
    }

    int set[_Z] = { 0 };
    int idxs[_ITEM] = { -1 };
    int cpt = _ITEM;

    while (1) {

        char citem = getchar();
        int  idx   = 0;

        if (citem == '\n') {
            continue;
        }

        idx = tetris_x11_setup_citem2idx(citem);
        set[idx] = 1;

        c = 0;
        for (n = 0; n < _Z; ++n) {
            if (set[n]) {
                ++c;
            }
        }
        if (c == _Z) {
            if (cpt == 0) {
                printf("setup completed\n");
                break; /* Setup Completed */
            }
            cpt--;
        }

        idxs[4] = idxs[3];
        idxs[3] = idxs[2];
        idxs[2] = idxs[1];
        idxs[1] = idxs[0];
        idxs[0] = idx;

        for (n = 0; idxs[n] != -1 && n < _ITEM; ++n) {

            c = _ITEM - n - 1;

            printf("block color get: %u, idx: %u\n", c, idxs[n]);

            tetris_x11_block_color_get(t11->d,
                                       t11->c[c].x[_UL], t11->c[c].x[_DR],
                                       t11->c[c].y[_UL], t11->c[c].y[_DR],
                                       &t11->rgb[c][idxs[n]]);
            printf("<item %c %u> (%u %u %u)\n", citem, idx,
                   t11->rgb[c][idxs[n]].r, t11->rgb[c][idxs[n]].g, t11->rgb[4][idxs[n]].b);
        }
    }

    return 0;
}

static inline char tetris_x11_item2char(int i)
{
    switch (i + 1) {
        case _I: return 'I';
        case _J: return 'J';
        case _L: return 'L';
        case _O: return 'O';
        case _S: return 'S';
        case _T: return 'T';
        case _Z: return 'Z';
    }
    return 'X';
}

int main(int argc, char **argv)
{
    tetris_x11_t t11;

    FILE *cfg = NULL;

    if (argc != 2) {
        fprintf(stderr, "./tetris_x11_setup config\n");
        return -1;
    }

    if ((cfg = fopen(argv[1], "w")) == NULL) {
        return -1;
    }

    tetris_x11_init(&t11);
    tetris_x11_setup(&t11);
    tetris_x11_config_save(&t11, cfg);
    tetris_x11_clean(&t11);

    fclose(cfg);

    return 0;
}
