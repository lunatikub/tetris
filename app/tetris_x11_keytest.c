#include <unistd.h>

#include "tetris_x11_keyboard.h"
#include "tetris_x11.h"

int main(void)
{
    tetris_x11_t t11;

    tetris_x11_init(&t11);

    int k[] = { XK_Left, XK_Left, XK_Z, XK_space };

    sleep(5);
    printf("GO\n");

    tetris_x11_keyboard_press(&t11, k, sizeof(k) / sizeof(int));

    tetris_x11_clean(&t11);

    return 0;
}
