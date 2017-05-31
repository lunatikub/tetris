#include <stdio.h>
#include <string.h>

#include "tetris_x11.h"

int tetris_x11_init(tetris_x11_t *t11)
{
    memset(t11, 0, sizeof(tetris_x11_t));

    t11->d = XOpenDisplay((char *)0);
    return 0;
}

static inline void tetris_x11_pixel_color_get(Display *d,
                                              int      x,
                                              int      y,
                                              rgb_t   *rgb)
{
    XImage *image = NULL;
    XColor color;

    image = XGetImage(d, RootWindow (d, DefaultScreen (d)), x, y, 1, 1, AllPlanes, XYPixmap);
    color.pixel = XGetPixel(image, 0, 0);
    XFree(image);
    XQueryColor(d, DefaultColormap(d, DefaultScreen (d)), &color);

    rgb->r = color.red;
    rgb->g = color.green;
    rgb->b = color.blue;
}

void tetris_x11_block_color_get(Display *d,
                                int      src_x,
                                int      dst_x,
                                int      src_y,
                                int      dst_y,
                                rgb_t   *rgb)
{
    int   x = 0;
    int   y = 0;
    rgb_t c = { 0, 0, 0 };

    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;

    for (x = src_x; x < dst_x; x += _INC) {
        for (y = src_y; y < dst_y; y += _INC) {
            tetris_x11_pixel_color_get(d, x, y, &c);
            rgb->r += c.r;
            rgb->g += c.g;
            rgb->b += c.b;
        }
    }
}

int tetris_x11_config_save(tetris_x11_t *t11,
                           FILE         *cfg)
{
    int i = 0;
    int j = 0;

    fprintf(cfg, "## Coord ##\n");

    for (i = 0; i < _ITEM; ++i) {
        fprintf(cfg, "\n # Item position %u\n", i);
        fprintf(cfg, "   (%u %u)\n", t11->c[i].x[_UL], t11->c[i].y[_UL]);
        fprintf(cfg, "   (%u %u)\n", t11->c[i].x[_DR], t11->c[i].y[_DR]);
    }

    fprintf(cfg, "\n## Colors ##\n");

    for (i = 0; i < _ITEM; ++i) {
        fprintf(cfg, "\n # Item position %u #\n", i);
        for (j = 0; j < _Z; ++j) {
            fprintf(cfg, "  # Item %u\n", j);
            fprintf(cfg, "    (%u %u %u)\n",
                    t11->rgb[i][j].r, t11->rgb[i][j].g, t11->rgb[i][j].b);
        }
    }

    return 0;
}

int tetris_x11_config_load(tetris_x11_t *t11,
                           FILE         *cfg)
{
    int i = 0;
    int j = 0;

    int x = 0;

    fscanf(cfg, "## Coord ##\n");
    fscanf(cfg, "\n");

    for (i = 0; i < _ITEM; ++i) {
        fscanf(cfg, " # Item position %u\n", &x);
        fscanf(cfg, "   (%u %u)\n", &t11->c[i].x[_UL], &t11->c[i].y[_UL]);
        fscanf(cfg, "   (%u %u)\n", &t11->c[i].x[_DR], &t11->c[i].y[_DR]);
    }

    fscanf(cfg, "\n## Colors ##\n");

    for (i = 0; i < _ITEM; ++i) {
        fscanf(cfg, "\n # Item position %u #\n", &x);

        for (j = 0; j < _Z; ++j) {
            fscanf(cfg, "  # Item %u\n", &x);
            fscanf(cfg,  "    (%u %u %u)\n",
                   &t11->rgb[i][j].r, &t11->rgb[i][j].g, &t11->rgb[i][j].b);
        }
    }

    return 0;
}

item_t tetris_x11_item_find(tetris_x11_t *t11,
                            rgb_t        *rgb,
                            int           n_item)
{
    int i = 0;
    int item = 0;

    int rgb_sub[_Z] = { 0 };

    for (i = 0; i < _Z; ++i) {
        rgb_sub[i] += abs(t11->rgb[n_item][i].r - rgb->r);
        rgb_sub[i] += abs(t11->rgb[n_item][i].g - rgb->g);
        rgb_sub[i] += abs(t11->rgb[n_item][i].b - rgb->b);

        if (rgb_sub[item] >= rgb_sub[i]) {
            item = i;
        }
    }

    return item + 1;
}

int tetris_x11_clean(tetris_x11_t *t11)
{
    XCloseDisplay(t11->d);
    return 0;
}

static inline int tetris_x11_items_fill(tetris_x11_t *t11,
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
    }

    return 0;
}

item_t tetris_x11_item_next(tetris_x11_t *t11,
                            item_t       *items)
{
    item_t curr_item = items[0];
    rgb_t rgb = { 0, 0, 0 };

    items[0] = items[1];
    items[1] = items[2];
    items[2] = items[3];
    items[3] = items[4];

    tetris_x11_block_color_get(t11->d,
                               t11->c[_ITEM - 1].x[_UL], t11->c[_ITEM - 1].x[_DR],
                               t11->c[_ITEM - 1].y[_UL], t11->c[_ITEM - 1].y[_DR],
                               &rgb);

    items[_ITEM - 1] = tetris_x11_item_find(t11, &rgb, _ITEM - 1);

    return curr_item;
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

int tetris_x11_game_start(tetris_x11_t *t11,
                          item_t       *items,
                          item_t       *curr_item)
{
    int  n  = 0;
    char fi = 0;

    printf("Start...\n");
    printf("First item (I/J/L/O/S/T/Z) ?: ");
    fi = getchar();

    fflush(stdout);

    switch (fi) {
        case 'I': *curr_item = _I; break;
        case 'J': *curr_item = _J; break;
        case 'L': *curr_item = _L; break;
        case 'O': *curr_item = _O; break;
        case 'S': *curr_item = _S; break;
        case 'T': *curr_item = _T; break;
        case 'Z': *curr_item = _Z; break;
        default:;
    }

    printf("items (y/n) ?\n");

    while (1) {
        tetris_x11_items_fill(t11, items);
        printf("  items:");
        for (n = 0; n < _ITEM; ++n) {
            printf("%c", item2char(items[n]));
        }
        printf("\r");
        char c = getchar();
        if (c == 'y' || c == 'Y') {
            break;
        }
    }

    return 0;
}
