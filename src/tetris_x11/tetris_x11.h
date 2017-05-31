#ifndef TETRIS_X11_H_
# define TETRIS_X11_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

#include "tetris.h"
#include "tetris_item.h"

#define _UL  (0) /* up-left */
#define _DR  (1) /* down-rigth */
#define _NRC (2) /* nr coord */

#define _R   (0) /* Red */
#define _G   (1) /* Green */
#define _B   (2) /* Blue */
#define _RGB (3)

#define _INC (5) /* incremental number of pixel for a block */

typedef struct {
    int x[_NRC];
    int y[_NRC];
} coord_t;

typedef struct {
    int r;
    int g;
    int b;
} rgb_t;

typedef struct {
    Display *d;                 /* Display */
    coord_t  c[_ITEM];          /* item coord */
    rgb_t    rgb[_ITEM][_Z];    /* item color */
} tetris_x11_t;

int tetris_x11_init(tetris_x11_t *t11);

int tetris_x11_clean(tetris_x11_t *t11);

int tetris_x11_config_save(tetris_x11_t *t11,
                           FILE         *cfg);

int tetris_x11_config_load(tetris_x11_t *t11,
                           FILE         *cfg);

void tetris_x11_block_color_get(Display *d,
                                int      src_x,
                                int      dst_x,
                                int      src_y,
                                int      dst_y,
                                rgb_t   *rgb);

item_t tetris_x11_item_find(tetris_x11_t *t11,
                            rgb_t        *rgb,
                            int           n_item);

int tetris_x11_game_start(tetris_x11_t *t11,
                          item_t       *items,
                          item_t       *curr_item);

item_t tetris_x11_item_next(tetris_x11_t *t11,
                            item_t       *items);

#endif /* !TETRIS_X11_H_ */
