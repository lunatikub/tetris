#ifndef TETRIS_X11_KEYBOARD_H_
# define TETRIS_X11_KEYBOARD_H_

#include "tetris_x11.h"

#define K_LEFT  (XK_Left)
#define K_RIGHT (XK_Right)
#define K_DROP  (XK_space)
#define K_ROT   (XK_X)
#define K_HOLD  (XK_C)

static inline char k2c(uint32_t k)
{
    switch (k) {
        case K_ROT:   return 'R';
        case K_HOLD:  return 'H';
        case K_LEFT:  return '<';
        case K_RIGHT: return '>';
        case K_DROP:  return 'D';
    }

    return 'X';
}

void tetris_x11_keyboard_press(tetris_x11_t *t11,
                               int          *k,
                               int           nr);

#endif /* !TETRIS_X11_KEYBOARD_H_ */
