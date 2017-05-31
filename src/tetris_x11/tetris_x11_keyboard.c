#include <unistd.h>

#include "tetris_x11_keyboard.h"

void tetris_x11_keyboard_press(tetris_x11_t *t11,
                               int          *k,
                               int           nr)
{
    uint32_t keycode = 0;
    int      n       = 0;

    for (n = 0; n < nr; ++n) {
        keycode = XKeysymToKeycode(t11->d, k[n]);
        XTestFakeKeyEvent(t11->d, keycode, True, 100);
        XTestFakeKeyEvent(t11->d, keycode, False, 100);
        XFlush(t11->d);
    }
}
